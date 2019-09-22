// TODO - need debug severity const for log

#include <cstring>
#include <thread>
#include "buffer_savers.hpp"
#include "workers.hpp"
#include <kodi/General.h>


class CircularBufferDataPackage: public Worker::DataPackage {
public:    
    CircularBufferDataPackage(std::vector<Worker::DataItem>& dataItems, int itemNum)
      : m_dataItems(dataItems), m_itemNum(itemNum) {}
    void SetFinishedWith() override { m_dataItems[m_itemNum].finishedWith = true; }
    void* GetData() const override { return m_dataItems[m_itemNum].data; }
    unsigned long GetTag() const override { return m_dataItems[m_itemNum].tag; }
    int ItemNum() const { return m_itemNum; }
private:
    std::vector<Worker::DataItem>& m_dataItems;
    const int m_itemNum;
};


Worker::Worker(size_t sizeofRequestDataItems, size_t sizeofProcessedDataItems) 
: m_sizeofRequestDataItems(sizeofRequestDataItems), 
  m_sizeofProcessedDataItems(sizeofProcessedDataItems),
  m_requestStore(g_maxRequestStoreLen),
  m_processedStore(g_maxProcessedStoreLen),
  m_currentRequestStoreItem(0),
  m_numMissedRequests(0),
  m_logger(nullptr),
  m_stop(false)
{
    for (int i=0; i < g_maxRequestStoreLen; i++) {
        m_requestStore[i].data = malloc(m_sizeofRequestDataItems);
    }
    for (int i=0; i < g_maxProcessedStoreLen; i++) {
        m_processedStore[i].data = malloc(m_sizeofProcessedDataItems);
    }

    Reset();
}    


Worker::~Worker() 
{
    for (int i=0; i < g_maxRequestStoreLen; i++) {
        free(m_requestStore[i].data);
    }
    for (int i=0; i < g_maxProcessedStoreLen; i++) {
        free(m_processedStore[i].data);
    }
}    


void Worker::Reset() 
{
    m_requestQueue.Reset();
    m_processedQueue.Reset();

    m_numMissedRequests = 0;

    for (int i=0; i < g_maxRequestStoreLen; i++) {
        m_requestStore[i].finishedWith = true;
        m_requestStore[i].tag = 0;
    }
    m_currentRequestStoreItem = 0;

    for (int i=0; i < g_maxProcessedStoreLen; i++) {
        m_processedStore[i].finishedWith = true;
        m_processedStore[i].tag = 0;
    }
}


void Worker::SetLogger(std::function<void (int, const std::string&)> logger)
{
    m_logger = logger;
}


void Worker::Log(int severity, const std::string& msg)
{
    if (m_logger == nullptr)
        return;

    m_logger(severity, msg);    
}


void Worker::SetInputDataProcessor(std::function<void (const void*, unsigned long, void*)> inputDataProcessor)
{
    m_inputDataProcessor = inputDataProcessor;
}


void Worker::AddRequest(const void* inputData, unsigned long tag) 
{
    std::lock_guard<std::mutex> lock(m_mutex); 

    const int prevRequestStoreItem = m_currentRequestStoreItem;
    m_currentRequestStoreItem = (m_currentRequestStoreItem + 1) % g_maxRequestStoreLen;
    if (!m_requestStore[m_currentRequestStoreItem].finishedWith) {
        Log(0, string_format("AddRequest: request item number %d with tag %lu not finished with - skipping add step.", m_currentRequestStoreItem, tag));
        m_numMissedRequests++;
        m_currentRequestStoreItem = prevRequestStoreItem;
        return;
    }

    std::memcpy(m_requestStore[m_currentRequestStoreItem].data, inputData, m_sizeofRequestDataItems);
    m_requestStore[m_currentRequestStoreItem].tag = tag;
    m_requestStore[m_currentRequestStoreItem].finishedWith = false;
    
    Worker::DataPackage* dataPackagePtr = new CircularBufferDataPackage(m_requestStore, m_currentRequestStoreItem);
    m_requestQueue.Push(dataPackagePtr);
    // Log(0, string_format("AddRequest: added request item number %d with tag %lu. ", m_currentRequestStoreItem, tag));

    if (tag == 109) {
      const short* audioBuff = reinterpret_cast<const short*>(m_requestStore[m_currentRequestStoreItem].data);  
      WriteFormattedArray(string_format(kodi::GetTempAddonPath("/request_buffer_%05d"), tag), "request", 
        m_requestStore[m_currentRequestStoreItem].tag, audioBuff, m_sizeofRequestDataItems/sizeof(short));
    }
}    


size_t Worker::RequestsQueueLength() const
{
    return m_requestQueue.Size();
}

bool Worker::RequestsQueueEmpty() const
{
    return m_requestQueue.Empty();
}


Worker::DataPackage* Worker::ProcessedPop()
{
    return m_processedQueue.Pop();
}

Worker::DataPackage* Worker::ProcessedTryPop()
{
    return m_processedQueue.TryPop();
}

size_t Worker::ProcessedQueueLength() const
{
    return m_processedQueue.Size();
}

bool Worker::ProcessedQueueEmpty() const
{
    return m_processedQueue.Empty();
}


void Worker::Thread() {
    Log(0, "Buffer worker: thread started.");

    m_stop = false;
    m_numMissedRequests = 0;
    int currentProcessedStoreItem = 0;
    while (!m_stop) {
        if (m_stop)
            break;

        const int prevProcessedStoreItem = currentProcessedStoreItem;
        currentProcessedStoreItem = (currentProcessedStoreItem + 1) % g_maxProcessedStoreLen;
        DataItem* currentItem = &(m_processedStore[currentProcessedStoreItem]);

        // Log(0, string_format("Buffer worker: checking processed item number %d with tag %lu.", currentProcessedStoreItem, currentItem->tag));
        if (!m_processedStore[currentProcessedStoreItem].finishedWith) {
            Log(0, string_format("Buffer worker: processed item number %d with tag %lu not finished with - skipping processing step.", currentProcessedStoreItem, currentItem->tag));
            currentProcessedStoreItem = prevProcessedStoreItem;
            continue;
        }

        if (m_stop)
            break;
        // Log(0, "Buffer worker: requesting an input buffer.");
        auto requestPtr = dynamic_cast<CircularBufferDataPackage*>(m_requestQueue.Pop());
        // Log(0, string_format("Buffer worker: got input buffer request item number %d with tag %lu.", requestPtr->ItemNum(), requestPtr->GetTag()));

        if (m_stop)
            break;
        // Log(0, string_format("Buffer worker: processing request data into processed item number %d.", currentProcessedStoreItem));
        currentItem->tag = requestPtr->GetTag();
        currentItem->finishedWith = false;
        m_inputDataProcessor(requestPtr->GetData(), requestPtr->GetTag(), currentItem->data);
        auto dataPackagePtr = new CircularBufferDataPackage(m_processedStore, currentProcessedStoreItem);
        requestPtr->SetFinishedWith();
        delete requestPtr;

        m_processedQueue.Push(dataPackagePtr);
        // Log(0, string_format("Buffer worker: pushed processed item number %d with tag %lu.", currentProcessedStoreItem, currentItem->tag));
    }

    Reset();
    Log(0, "Buffer worker: thread stopped.");
}    

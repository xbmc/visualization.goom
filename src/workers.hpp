#ifndef WORKERS_HPP
#define WORKERS_HPP

#include <thread>
#include <mutex>
#include <atomic>
#include <functional>
#include "tsqueue.hpp"


class Worker {
public:
    class DataPackage {
    public:
        virtual ~DataPackage() {}
        virtual void SetFinishedWith()=0;
        virtual void* GetData() const=0;
        virtual unsigned long GetTag() const=0;
    };
public:    
    Worker(size_t sizeofRequestDataItems, size_t sizeofProcessedDataItems);
    virtual ~Worker();
    void SetLogger(std::function<void (int, const std::string&)>);

    void AddRequest(const void* inputData, unsigned long tag);
    unsigned long NumMissedRequests() const { return m_numMissedRequests; };
    size_t RequestsQueueLength() const;
    bool RequestsQueueEmpty() const;

    void SetInputDataProcessor(std::function<void (const void*, unsigned long, void*)>);
    DataPackage* ProcessedPop();
    DataPackage* ProcessedTryPop();
    size_t ProcessedQueueLength() const;
    bool ProcessedQueueEmpty() const;

    void Thread();
    void Stop() { m_stop = true; }
private:
    const size_t m_sizeofRequestDataItems;
    tsqueue<DataPackage*> m_requestQueue;
    unsigned long m_numMissedRequests;

    const size_t m_sizeofProcessedDataItems;
    tsqueue<DataPackage*> m_processedQueue;
    std::function<void (const void*, unsigned long, void*)> m_inputDataProcessor;

    bool m_stop;
    mutable std::mutex m_mutex; 
    std::function<void (int, const std::string&)> m_logger;
    void Log(int, const std::string&);
    void Reset();

    struct DataItem {
        std::atomic<bool> finishedWith;
        void* data;
        unsigned long tag;
    };
    friend class CircularBufferDataPackage;
    const static int g_maxRequestStoreLen = 1000;
    std::vector<DataItem> m_requestStore;
    int m_currentRequestStoreItem;
    const static int g_maxProcessedStoreLen = 5;
    std::vector<DataItem> m_processedStore;
};

#endif

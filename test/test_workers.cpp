// Compile and link with
//
//  g++ -g -std=c++11 test_workers.cpp workers.cpp -lpthread -o test_workers


#include <iostream>
#include <thread>
#include "../src/workers.hpp"


void sleep_for_debugging(int time_ms=100)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(time_ms + rand() % time_ms));
}


const int inputBufferLen = 2;
const int inputBufferSize = inputBufferLen*sizeof(int);
const int outputBufferLen = 4;
const int ouputBufferSize = outputBufferLen*sizeof(int);

std::string getBuffer(int buffLen, int* inBuffer)
{
    std::string s = "";
    for (int i=0; i < buffLen; i++) 
    {
        s += std::to_string(inBuffer[i]) + " ";
    }
    return s;
}

std::string getInBuffer(void* inBuffer)
{
    return getBuffer(inputBufferLen, (int*)inBuffer);
}

std::string getOutBuffer(void* outBuffer)
{
    return getBuffer(outputBufferLen, (int*)outBuffer);
}


void InputProcessor(void* inBuffer, void* outBuffer)
{
    int* inBuff = (int*)inBuffer;
    int* outBuff = (int*)outBuffer;
    for (int i=0; i < inputBufferLen; i++) 
    {
        outBuff[i] = inBuff[i];
        outBuff[i+2] = 2*inBuff[i];
    }
}

void Logger(const std::string& msg)
{
    std::cout << msg << std::endl;    
}


int main()
{
    Worker worker(inputBufferSize, ouputBufferSize);
    worker.SetInputDataProcessor(InputProcessor);
    worker.SetLogger(Logger);
    std::thread thrwork(&Worker::Thread, &worker);

    std::cout << "Start 'pushing' input data...\n\n";
    for(int i = 0; i < 10; i++)
    {
        if (i == 8) {
            worker.AddRequest(0);
            std::cout << "push iter " << i << ": pushed input repeated request data " << i-1 << "\n\n";
        }

        worker.AddRequest([&](void* inbuff){ int* buff = (int*)inbuff; buff[0]=i; buff[1]=i+1; });
        std::cout << "push iter " << i << ": pushed input request data " << i << "\n\n";

        sleep_for_debugging();

        auto dataPackage = worker.ProcessedTryPop();
        if (dataPackage == nullptr) {
          std::cout << "push iter " << i << ": no output data ready.\n\n";
        } else {    
          std::cout << "push iter " << i << ": got output data '" << getOutBuffer(dataPackage->GetData()) << "'\n\n";
          dataPackage->SetFinishedWith();
        }
    }

    worker.Stop();
    thrwork.detach();

    std::cout << "\nFinished all pushing - now waiting for empty...\n";
    while (!worker.ProcessedQueueEmpty()) {
      auto dataPackage = worker.ProcessedTryPop();
      std::cout << "Emptying processed queue: got output data '" << getOutBuffer(dataPackage->GetData()) << "'\n";
      dataPackage->SetFinishedWith();
      sleep_for_debugging(10);
    }
    std::cout << "Processed queue has been emptied.\n\n";

    std::cout << "This must be the last line." << std::endl;
}

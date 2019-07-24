// Compile with
//
// g++ -std=c++11 test_tsqueue.cpp -lpthread -o test_tsqueue


#include <iostream>
#include <thread>
#include "../src/tsqueue.hpp"


void sleep_for_debugging(int time_ms=100)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(time_ms + rand() % time_ms));
}


class ThreadTester {
public:    
    ThreadTester(tsqueue<int>& _inputQueue, tsqueue<std::string>& _outputQueue)
      : inputQueue(_inputQueue), outputQueue(_outputQueue) {}
    void Popper();
    void TryPopper();
    void Stop() { stop = true; }
private:
    tsqueue<int>& inputQueue;
    tsqueue<std::string>& outputQueue;
    bool stop = false;
    int N = 100;
};

void ThreadTester::Popper() {
    std::cout << "Start 'popping' thread...\n";
    for(int i=0; i < N/2; i++)
    {
        std::cout << "pop iter " << i <<": popping...\n";
        std::shared_ptr<int> data = inputQueue.Pop();
        std::cout << "-- popped data - " << *data << "\n\n";
        outputQueue.Push(std::string("out " + std::to_string(i)));
        sleep_for_debugging();
    }
}    

void ThreadTester::TryPopper() {
    std::cout << "Start 'try popping' thread...\n";
    int i = 0;
    while(!stop || !inputQueue.Empty())
    {
        std::cout << "try pop iter " << i << ": try for pop...\n";
        std::shared_ptr<int> data = inputQueue.TryPop();
        if (data.get() != 0)
        {
            std::cout << "-- try popped data - " << *data << "\n\n";
            outputQueue.Push(std::string("out " + std::to_string(i)));
        }
        else {
            std::cout << "-- try pop failed \n\n";
        }
        sleep_for_debugging(50);
        i++;
    }
}


void test_tsq()
{
    /**
    std::thread thrpush([&]{
        std::cout << "Start 'pushing' thread...\n";
        for(int i=0;i<N;i++)
        {
            tsq.Push(i);
            std::cout <<i<<": pushed \n";
            sleep_for_debugging();
        }
        std::cout << "Finished all pushing - now waiting...\n";
        sleep_for_debugging(2000);
    });
    **/
    tsqueue<int> inputQueue;
    tsqueue<std::string> outputQueue;
    ThreadTester tester(inputQueue, outputQueue);
    std::thread thrpop(&ThreadTester::Popper, &tester);
    std::thread thrtrypop(&ThreadTester::TryPopper, &tester);

    std::cout << "Start 'pushing'...\n";
    for(int i = 0; i < 100; i++)
    {
        inputQueue.Push(i);
        std::cout << "push iter " << i << ": pushed data " << i << "\n\n";
        sleep_for_debugging();
        std::shared_ptr<std::string> data = outputQueue.TryPop();
        if (data.get() != 0) {
          std::cout << "push iter " << i << ": gout output data '" << i << "'\n\n";
        }
    }
    tester.Stop();
    std::cout << "\nFinished all pushing - now waiting for empty...\n";
    while (!inputQueue.Empty()) {
      sleep_for_debugging(10);
    }
    std::cout << "Input queue has been emptied.\n\n";

//    thrpush.join();
//    thrpop.join();
//    thrtrypop.join();
    thrpop.detach();
    thrtrypop.detach();
}


int main()
{
  std::cout << "Hi, Welcome to demo of thread safe queue." << std::endl << std::endl;
  
  test_tsq();

  std::cout << "This must be the last line." << std::endl;
}

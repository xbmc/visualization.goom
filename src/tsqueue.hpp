#ifndef TSQUEUE_HPP
#define TSQUEUE_HPP

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>


template <class T> class tsqueue {
public:
    void Push(T pValue)
    {
        // Block execution here, if another thread already locked m_mutex!
        std::lock_guard<std::mutex> lock(m_mutex); 
        // if we are here, then no other thread is owned/locked by m_mutex. So we can modify the internal data.
        m_data.push(pValue); 
        // OK! Notify threads which were blocked because of queue empty and make them happy!
        m_emptyCondition.notify_all();
    } 
    // Now m_mutex is unlocked in destructor of lock_guard!
 
    T Pop()
    {
        // Own the m_mutex like in Push method except that lock can be unlocked manually without the need for the lock destructor!
        std::unique_lock<std::mutex> lock(m_mutex); 
        // If we are here, m_mutex is locked and no other thread can access/modify the data!
        //   wait() method first checks if m_data is not empty, then allows execution to go on. 
        // Else:
        //   unlocks the m_mutex and waits for signal.
        // Because m_mutex is released other threads have a chance to Push new data into queue 
        // ... in notify this condition variable!
        m_emptyCondition.wait(lock, [this]{ return !m_data.empty(); });
        // If we are are here, m_data is not empty and m_mutex is locked!
        auto ret = m_data.front();
        m_data.pop();
        return ret;
    }

    T TryPop()
    {
        std::lock_guard<std::mutex> lock(m_mutex); 
        if (m_data.empty())
            return 0;
        auto ret = m_data.front();
        m_data.pop();
        return ret;
    }

    T Front()
    {
        std::lock_guard<std::mutex> lock(m_mutex); 
        if (m_data.empty())
            return 0;
        return m_data.front();
    }

    bool Empty() const
    {
        std::lock_guard<std::mutex> lock(m_mutex); 
        return m_data.empty();
    }

    size_t Size() const
    {
        std::lock_guard<std::mutex> lock(m_mutex); 
        return m_data.size();
    }

    void Reset()
    {
      std::queue<T> empty;
      m_data.swap(empty);
    }

private :
    std::queue<T> m_data;
    mutable std::mutex m_mutex; 
    std::condition_variable m_emptyCondition;
};

#endif

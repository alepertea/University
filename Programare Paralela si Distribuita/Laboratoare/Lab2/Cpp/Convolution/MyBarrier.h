#pragma once
#include <mutex>

using namespace std;

class MyBarrier
{
private:
    mutex mtx;
    condition_variable conditionVariable;
    int counter;
    int waiting;
    int thread_count;
public:
    MyBarrier(int count) : thread_count(count), counter(0), waiting(0) { }
    void wait()
    {
        unique_lock<mutex> lock(mtx);
        ++counter;
        ++waiting;
        conditionVariable.wait(lock, [&] {return counter >= thread_count; });
        conditionVariable.notify_one();
        --waiting;
        if (waiting == 0)
        {
            counter = 0;
        }
        lock.unlock();
    }
};
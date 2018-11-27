// threadpool.cpp
// Compile with:
// g++ -std=c++11 -pthread threadpool.cpp -o threadpool

#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <deque>
#include <functional>
#include <condition_variable>

class ThreadPool; // forward declare

class Worker
{
  public:
    Worker(ThreadPool &s) : pool(s) {}
    void operator()();

  private:
    ThreadPool &pool;
};

class ThreadPool
{
  public:
    ThreadPool(size_t threads);
    template <class F>
    void enqueue(F f);
    std::condition_variable cond; // Condition used for thread notifying
    ~ThreadPool();

  private:
    friend class Worker;

    std::vector<std::thread> workers;
    std::deque<std::function<void()>> tasks;
    std::mutex queue_mutex;
    bool stop;
};

void Worker::operator()()
{
    std::function<void()> task;
    while (true)
    {
        std::unique_lock<std::mutex> locker(pool.queue_mutex);
        pool.cond.wait(locker, [&] { return !pool.tasks.empty() || pool.stop; }); // Waits for signal from enqueue() or ~ThreadPool()
        if (pool.stop)
        {
            return;
        }
        if (!pool.tasks.empty())
        {
            task = pool.tasks.front();
            pool.tasks.pop_front();
            locker.unlock();
            task();
            pool.cond.notify_one(); // Notifies any next thread if done
        }
        else
        {
            locker.unlock();
        }
    }
}

ThreadPool::ThreadPool(size_t threads) : stop(false)
{
    for (size_t i = 0; i < threads; ++i)
        workers.push_back(std::thread(Worker(*this)));
}

ThreadPool::~ThreadPool()
{
    stop = true; // stop all threads

    cond.notify_all();

    for (auto &thread : workers)
    {
        thread.join();
    }
}

template <class F>
void ThreadPool::enqueue(F f)
{
    std::unique_lock<std::mutex> lock(queue_mutex);
    tasks.push_back(std::function<void()>(f));
    lock.unlock();
    cond.notify_one(); // Sends signal to operator()
}

void greet(int i) // to_string prevents weird console output
{
    std::cout << "Hello from work item " + std::to_string(i) + "\n"; // <== Correct output.
    // std::cout << "Hello from work item " << i << std::endl;       // <== Gives strange, jumbled output.
}

int main()
{
    ThreadPool pool(4);

    // queue a bunch of "work items"
    for (int i = 0; i < 16; ++i)
        pool.enqueue([i]() { greet(i); });

    // wait for keypress to give worker threads the opportunity to finish tasks
    std::cin.ignore();

    return 0;
}

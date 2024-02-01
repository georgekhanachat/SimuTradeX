#ifndef SIMUTRADEX_THREADSAFEQUEUE_H
#define SIMUTRADEX_THREADSAFEQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() = default;

    void push(T value) {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(std::move(value));
        cond_var.notify_one();
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lock(mtx);
        if (queue.empty()) {
            return false;
        }
        value = std::move(queue.front());
        queue.pop();
        return true;
    }

    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lock(mtx);
        cond_var.wait(lock, [this]{ return !queue.empty(); });
        value = std::move(queue.front());
        queue.pop();
    }

private:
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable cond_var;
};


#endif //SIMUTRADEX_THREADSAFEQUEUE_H

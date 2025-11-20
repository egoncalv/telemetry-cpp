//
// Created by Erick Gonçalves on 19/11/2025.
//

#pragma once
#include <queue>
#include <mutex>

template <typename T>
class SafeQueue {
public:
    void push(T value) {
        std::lock_guard lock(mMutex);
        mQueue.push(std::move(value));
        mCondition.notify_one();
    };
    T pop() {
        std::unique_lock lock(mMutex);
        mCondition.wait(lock, [this]() {
            return !mQueue.empty();
        });
        T value = std::move(mQueue.front());
        mQueue.pop();
        return value;
    };

    T tryPopFor(const std::chrono::milliseconds& timeoutDuration) {
        std::unique_lock lock(mMutex);
        if (!mCondition.wait_for(lock, timeoutDuration, [this]() { return !mQueue.empty(); })) {
            throw std::runtime_error("Timeout while waiting to pop from SafeQueue");
        }
        T value = std::move(mQueue.front());
        mQueue.pop();
        return value;
    }
private:
    std::queue<T> mQueue;
    std::mutex mMutex;
    std::condition_variable mCondition;
};
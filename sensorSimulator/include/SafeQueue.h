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
private:
    std::queue<T> mQueue;
    std::mutex mMutex;
    std::condition_variable mCondition;
};
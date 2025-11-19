//
// Created by Erick Gonçalves on 19/11/2025.
//

#pragma once
#include <queue>
#include <mutex>

template <typename T>
class SafeQueue {
public:
    void push(T value);
    T pop();
private:
    std::queue<T> mQueue;
    std::mutex mMutex;
    std::condition_variable mCondition;
};
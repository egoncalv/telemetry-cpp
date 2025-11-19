//
// Created by Erick Gonçalves on 19/11/2025.
//

#include "../include/SafeQueue.h"

template <typename T>
void SafeQueue<T>::push(T value) {
    std::lock_guard lock(mMutex);
    mQueue.push(std::move(value));
    mCondition.notify_one();
}

template <typename T>
T SafeQueue<T>::pop() {
    std::unique_lock lock(mMutex);
    mCondition.wait(lock, [this]() {
        return !mQueue.empty();
    });
    T value = std::move(mQueue.front());
    mQueue.pop();
    return value;
}

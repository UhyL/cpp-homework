#include "Concurrency.h"
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <string>

int sum = 0;
// TODO: Task1-1 define a lock of type `std::mutex` here
std::mutex mtx;

void increment() {
    // TODO: Task1-1 increment the variable `sum` by 1
    // You need to think about how to guarantee the atomicity of `sum` self-incrementing 1
    std::lock_guard<std::mutex> guard(mtx);
    sum++;
}

std::atomic<int> atomic_sum(0);

void init_sum(int value) {
    // TODO: Task1-2 set the value of `atomic_sum` atomically
    // The purpose of defining functions in this way is for teaching purposes
    atomic_sum.store(value);
}

void atomic_increment(int v) {
    // TODO: Task1-2 increment the variable `sum` by v
    atomic_sum.fetch_add(v);
}

std::mutex bracket_mtx;
std::condition_variable cv;
std::string brackets; // store the brackets

// TODO: Task2 Define some global variable and locks for task2.
// All tests are independent, so you don't need to think about the initialization of these global variables

int curr_length = 0;

void produce(int k) {
    // TODO: Task2 Atomically put an opening bracket '(' at the end of 'brackets' at a time.

    std::unique_lock<std::mutex> lock(bracket_mtx);
    cv.wait(lock, [&]() { return curr_length < k; });

    brackets.push_back('(');
    ++curr_length;

    cv.notify_all();
}

void consume([[maybe_unused]] int k) {
    // TODO: Task2 Atomically put an opening bracket ')' at the end of 'brackets' at a time.

    std::unique_lock<std::mutex> lock(bracket_mtx);
    cv.wait(lock, [&]() { return curr_length > 0; });

    brackets.push_back(')');
    --curr_length;

    cv.notify_all();
}

// === The following functions will only be used in test cases ===

void slow_increment(int times) {
    for (int i = 0; i < times; ++i) {
        increment();
    }
}

void quick_increment(int times, int v) {
    for (int i = 0; i < times; ++i) {
        atomic_increment(v);
    }
}

void producer_thread(int times, int k) {
    for (int i = 0; i < times; ++i) {
        produce(k);
    }
}

void consumer_thread(int times, int k) {
    for (int i = 0; i < times; ++i) {
        consume(k);
    }
}
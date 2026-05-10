#pragma once
#include <atomic>
#include <chrono>
#include <functional>

using namespace std;

class Scheduler
{
public:
    Scheduler();
    void run(const function<void()>& task,chrono::seconds interval);
    void stop();
private:
    atomic<bool> running_;
};
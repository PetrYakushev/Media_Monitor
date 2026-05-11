#include "../insert/Scheduler.h"

#include <thread>

Scheduler::Scheduler(): running_(true){}

void Scheduler::run(const function<void()>& task,chrono::seconds interval){
    while (running_){
        task();
        if (!running_){
            break;
        }
        this_thread::sleep_for(interval);
    }
}

void Scheduler::stop(){
    running_ = false;
}
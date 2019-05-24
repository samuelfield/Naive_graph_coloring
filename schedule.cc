#include "schedule.hh"

Scheduler::Scheduler(uint32_t size, bool initializer)
{
    schedule.resize(size);
    std::fill(schedule.begin(), schedule.end(), initializer);
}

Scheduler::~Scheduler()
{
}

void Scheduler::setItem(uint32_t item, bool trigger)
{
    std::lock_guard<std::mutex> guard(scheduleMutex);
    schedule[item] = trigger;
}

bool Scheduler::checkItem(uint32_t item)
{
    std::lock_guard<std::mutex> guard(scheduleMutex);
    return schedule[item];
}

bool Scheduler::notDone()
{
    std::lock_guard<std::mutex> guard(scheduleMutex);
    for (auto &&i : schedule)
    {
        if (i)
            return true;
    }
    
    return false;
}
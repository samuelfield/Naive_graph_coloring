#include <vector>
#include <inttypes.h>
#include <mutex>

class Scheduler
{
private:
    std::mutex scheduleMutex;
    std::vector<bool> schedule;
public:
    Scheduler(uint32_t size, bool initializer = true);
    ~Scheduler();

    void Scheduler::setItem(uint32_t item, bool trigger);
    bool Scheduler::checkItem(uint32_t item);
    bool Scheduler::notDone();
};


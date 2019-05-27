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

    void setItem(uint32_t item, bool trigger);
    bool checkItem(uint32_t item);
    bool completed();
};


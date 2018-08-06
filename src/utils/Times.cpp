#include <utils/Times.hpp>
#include <time.h>

namespace GameEngine
{
    Timer::Timer()
    {
        clock_gettime(CLOCK_REALTIME, &this->_start);
        this->_freq = this->_start.tv_sec + this->_start.tv_nsec / 1000000000.0;
    }

    void Timer::reset()
    {
        clock_gettime(CLOCK_REALTIME, &this->_start);
    }

    float Timer::elapsed()
    {
        struct timespec current;
        clock_gettime(CLOCK_REALTIME, &current);

        return current.tv_sec - this->_start.tv_sec;
    }
}
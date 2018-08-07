#include <utils/Times.hpp>
#include <time.h>

namespace GameEngine
{
    Timer::Timer()
    {
        gettimeofday(&this->_start, NULL);
    }

    void Timer::reset()
    {
        gettimeofday(&this->_start, NULL);
    }

    double Timer::elapsed()
    {
        timeval current;
        gettimeofday(&current, NULL);

        return current.tv_sec - this->_start.tv_sec;
    }

    double Timer::elapsed_ms()
    {
        timeval current;
        gettimeofday(&current, NULL);

        return (current.tv_sec - this->_start.tv_sec) * 1000;
    }

    double Timer::elapsed_us()
    {
        timeval current;
        gettimeofday(&current, NULL);

        return current.tv_usec - this->_start.tv_usec;
    }
}
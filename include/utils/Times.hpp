#ifndef TIMES_HPP
#define TIMES_HPP

#include <sys/time.h>

namespace GameEngine
{
    class Timer
    {
        public:
            Timer();
            ~Timer();
            void reset();
            double elapsed();
            double elapsed_ms();
            double elapsed_us();

        private:
            timeval _start;
            double _freq;

    };
}

#endif
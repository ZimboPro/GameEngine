#ifndef TIMES_HPP
#define TIMES_HPP

#include <sys/_types/_timespec.h>
#include <Kernel/sys/_types/_timespec.h>
#include <Kernel/sys/_types/_user32_timespec.h>
#include <Kernel/sys/_types/_user64_timespec.h>
#include <Kernel/sys/_types/_user_timespec.h>

namespace GameEngine
{
    class Timer
    {
        public:
            Timer();
            ~Timer();
            void reset();
            float elapsed();

        private:
            struct timespec _start;
            double _freq;

    };
}

#endif
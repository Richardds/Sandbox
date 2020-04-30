#pragma once

#include <chrono>

#include "../Core/Types.h"

namespace Timing
{
    
    class Time
    {
    public:
        Time();
        Time(const Time& time);
        Time(TimePoint time);
        virtual ~Time();
        void operator=(const Time& rhs);
        Duration Diff(Time time) const;
        template<typename T>
        T Get() const;

        static Time Now();

    private:
        TimePoint _time;
    };

    template<typename T>
    inline T Time::Get() const
    {
        return std::chrono::duration_cast<T>(this->_time.time_since_epoch());
    }

}

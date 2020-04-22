#pragma once

#include <chrono>

namespace Timing
{

    using namespace std::chrono;

    typedef time_point<steady_clock, microseconds> TimePoint;
    typedef nanoseconds Duration;
    
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
        return duration_cast<T>(this->_time.time_since_epoch());
    }

}

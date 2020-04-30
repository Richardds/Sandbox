#include "Time.h"

Timing::Time::Time() :
    _time()
{
}

Timing::Time::Time(const Time& rhs)
{
    this->_time = rhs._time;
}

Timing::Time::Time(TimePoint time) :
    _time(time)
{
}

Timing::Time::~Time()
{
}

void Timing::Time::operator=(const Time& rhs)
{
    this->_time = rhs._time;
}

Timing::Duration Timing::Time::Diff(Time rhs) const
{
    return std::chrono::duration_cast<Duration>(this->_time - rhs._time);
}

Timing::Time Timing::Time::Now()
{
    return std::chrono::time_point_cast<Microseconds>(std::chrono::steady_clock::now());
}

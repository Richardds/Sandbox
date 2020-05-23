// ----------------------------------------------------------------------------------------
//  \file       Time.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Timing/Time.h"

Timing::Time::Time(const Time& rhs)
{
	this->_time = rhs._time;
}

Timing::Time::Time(const TimePoint time) :
	_time(time)
{
}

Timing::Duration Timing::Time::Diff(const Time& rhs) const
{
	return std::chrono::duration_cast<Duration>(this->_time - rhs._time);
}

Timing::Time Timing::Time::Now()
{
	return Time(std::chrono::time_point_cast<Microseconds>(std::chrono::steady_clock::now()));
}

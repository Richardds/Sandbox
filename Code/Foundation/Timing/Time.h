#pragma once

#include "Precompiled.h"
#include "Core/Types.h"

namespace Timing
{
	class Time
	{
	public:
		Time() = default;
		Time(const Time& rhs);
		explicit Time(TimePoint time);
		void operator=(const Time& rhs);
		[[nodiscard]] Duration Diff(const Time& rhs) const;
		template <typename T>
		[[nodiscard]] T Get() const;

		static Time Now();

	private:
		TimePoint _time;
	};

	template <typename T>
	T Time::Get() const
	{
		return std::chrono::duration_cast<T>(this->_time.time_since_epoch());
	}
}

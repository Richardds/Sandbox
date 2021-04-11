// ----------------------------------------------------------------------------------------
//  \file       Time.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Types.h"

namespace Timing
{
    /// Simple std::chrono time wrapper
    class EXPORT Time final
    {
    public:
        Time() = default;
        Time(const Time& rhs);
        explicit Time(TimePoint time);

        Duration Diff(const Time& rhs) const;
        template <typename T>
        T Get() const;

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

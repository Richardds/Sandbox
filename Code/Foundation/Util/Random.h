// ----------------------------------------------------------------------------------------
//  \file       Random.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Core/Singleton.h"

namespace Util
{
    /// std::random wrapper
    class EXPORT Random final
    {
    _Singleton(Random)

    public:
        Random();

        template <typename T>
        T GetInt(T min, T max);
        template <typename T>
        T GetReal(T min, T max);
        bool GetBool(double chance = 0.5);
        float GetAngle();

    private:
        std::mt19937 _random;
    };

    template <typename T>
    T Random::GetInt(const T min, const T max)
    {
        const std::uniform_int_distribution<T> distribution(min, max);
        return distribution(this->_random);
    }

    template <typename T>
    T Random::GetReal(const T min, const T max)
    {
        const std::uniform_real_distribution<T> distribution(min, max);
        return distribution(this->_random);
    }
}

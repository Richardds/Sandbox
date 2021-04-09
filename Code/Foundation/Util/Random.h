// ----------------------------------------------------------------------------------------
//  \file       Random.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Singleton.h"

namespace Util
{
    /// std::random wrapper
    class EXPORT Random
    {
    _Singleton(Random)

    public:
        Random() = default;
        virtual ~Random() = default;

        template <typename T>
        T GetInt(T min, T max);
        template <typename T>
        T GetReal(T min, T max);
        float GetAngle();

    private:
        std::random_device _random;
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

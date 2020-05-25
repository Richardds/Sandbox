// ----------------------------------------------------------------------------------------
//  \file       Random.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Util/Random.h"

Util::Random::Random() :
    _random(std::random_device()())
{
}

float Util::Random::GetAngle()
{
    return this->GetReal(0.0f, 360.0f - std::numeric_limits<float>::epsilon());
}

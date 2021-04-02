// ----------------------------------------------------------------------------------------
//  \file       Random.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Util/Random.h"

float Util::Random::GetAngle()
{
    return this->GetReal(0.0f, 360.0f - std::numeric_limits<float>::epsilon());
}
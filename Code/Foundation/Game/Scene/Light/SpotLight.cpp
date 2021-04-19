// ----------------------------------------------------------------------------------------
//  \file       SpotLight.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Game/Scene/Light/SpotLight.h"

Graphics::SpotLight::SpotLight() :
    _cutOffAngle(DEFAULT_CUT_OFF_ANGLE),
    _outerCutOffAngleOffset(DEFAULT_CUT_OFF_ANGLE_OFFSET)
{
}

float Graphics::SpotLight::GetCosineCutOffAngle() const
{
    return glm::cos(glm::radians(this->_cutOffAngle));
}

float Graphics::SpotLight::GetCosineOuterCutOffAngle() const
{
    return glm::cos(glm::radians(this->_cutOffAngle + this->_outerCutOffAngleOffset));
}

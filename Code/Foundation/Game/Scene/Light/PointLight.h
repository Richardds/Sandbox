// ----------------------------------------------------------------------------------------
//  \file       PointLight.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Game/Scene/Light.h"
#include "Game/Attributes/HasPosition3D.h"

namespace Graphics
{
    /// 3D scene point light entity
    class EXPORT PointLight : public Light, public HasPosition3D
    {
    public:
        PointLight();

        Math::Vector3f GetAttenuation() const;
        void SetAttenuation(const Math::Vector3f& attenuation);

    private:
        Math::Vector3f _attenuation;
    };

    inline Math::Vector3f PointLight::GetAttenuation() const
    {
        return this->_attenuation;
    }

    inline void PointLight::SetAttenuation(const Math::Vector3f& attenuation)
    {
        this->_attenuation = attenuation;
    }
}

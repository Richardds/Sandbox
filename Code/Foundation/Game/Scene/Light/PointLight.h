// ----------------------------------------------------------------------------------------
//  \file       PointLight.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Game/Scene/Light.h"
#include "Game/Attributes/HasPosition.h"

namespace Graphics
{
    /// 3D scene point light entity
    class EXPORT PointLight : public Light, public HasPosition
    {
    public:
        PointLight();
        virtual ~PointLight() = default;

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

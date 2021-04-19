// ----------------------------------------------------------------------------------------
//  \file       DirectionalLight.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Game/Scene/Light.h"

namespace Graphics
{
    /// 3D scene directional light entity
    class EXPORT DirectionalLight : public Light
    {
    public:
        DirectionalLight();

        Math::Vector3f GetDirection() const;
        void SetDirection(const Math::Vector3f& direction);

    private:
        Math::Vector3f _direction;
    };

    inline Math::Vector3f DirectionalLight::GetDirection() const
    {
        return this->_direction;
    }

    inline void DirectionalLight::SetDirection(const Math::Vector3f& direction)
    {
        this->_direction = direction;
    }
}

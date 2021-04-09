// ----------------------------------------------------------------------------------------
//  \file       SpotLight.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Game/Scene/Light/DirectionalLight.h"
#include "Game/Attributes/HasPosition.h"

namespace Graphics
{
    /// 3D scene spot light entity
    class EXPORT SpotLight : public DirectionalLight, public HasPosition
    {
    public:
        /// Spot light cut-off angle when undefined
        static constexpr float DEFAULT_CUT_OFF_ANGLE = 12.5f;
        /// Spot light cut-off angle offset when undefined
        static constexpr float DEFAULT_CUT_OFF_ANGLE_OFFSET = 5.0f;

        SpotLight();
        virtual ~SpotLight() = default;

        float GetCutOffAngle() const;
        float GetCosineCutOffAngle() const;
        void SetCutOffAngle(float cutOffAngle);
        float GetOuterCutOffAngle() const;
        float GetCosineOuterCutOffAngle() const;
        float GetOuterCutOffAngleOffset() const;
        void SetOuterCutOffAngleOffset(float outerCutOffAngleOffset);

    private:
        float _cutOffAngle;
        float _outerCutOffAngleOffset;
    };

    inline float SpotLight::GetCutOffAngle() const
    {
        return this->_cutOffAngle;
    }

    inline void SpotLight::SetCutOffAngle(const float cutOffAngle)
    {
        this->_cutOffAngle = cutOffAngle;
    }

    inline float SpotLight::GetOuterCutOffAngle() const
    {
        return this->_cutOffAngle + this->_outerCutOffAngleOffset;
    }

    inline float SpotLight::GetOuterCutOffAngleOffset() const
    {
        return this->_outerCutOffAngleOffset;
    }

    inline void SpotLight::SetOuterCutOffAngleOffset(const float outerCutOffAngleOffset)
    {
        this->_outerCutOffAngleOffset = outerCutOffAngleOffset;
    }

}

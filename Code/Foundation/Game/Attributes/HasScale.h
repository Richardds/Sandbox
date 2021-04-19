// ----------------------------------------------------------------------------------------
//  \file       HasScale.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"

namespace Graphics
{
    /// Provides scale attributes and operations
    class EXPORT HasScale
    {
    public:
        HasScale();
        explicit HasScale(float scale);
        virtual ~HasScale() = default;

        float GetScale() const;
        void SetScale(float scale);
        void IncreaseScale(float scale);

    protected:
        float _scale;
    };

    inline float HasScale::GetScale() const
    {
        return this->_scale;
    }

    inline void HasScale::SetScale(const float scale)
    {
        this->_scale = scale;
    }
}

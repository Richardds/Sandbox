// ----------------------------------------------------------------------------------------
//  \file       GraphicsUtils.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/Core.h"
#include "Math/Vector.h"

namespace Graphics
{
    inline Math::Vector2f PixelToNDCScale(const Math::Vector2f& coordinates)
    {
        const Math::Vector2f screenResolution = Core::Instance().GetResolution();
        return 2.0f * (coordinates / screenResolution);
    }
}

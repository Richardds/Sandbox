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
    /**
     * Converts top-left absolute pixel coordinates to bottom-left relative screen coordinates
     */
    EXPORT inline Math::Vector2f PixelToNDCScale(const Math::Vector2f& coordinates, const Math::Vector2f& screenResolution)
    {
        return 2.0f * (coordinates / screenResolution);
    }

    /**
     * Converts top-left absolute pixel coordinates to bottom-left relative screen coordinates
     */
    EXPORT inline Math::Vector2f PixelToNDCScale(const Math::Vector2f& coordinates)
    {
        return PixelToNDCScale(coordinates, Core::Instance().GetResolution());
    }

    /**
     * Converts top-left absolute pixel coordinates to bottom-left relative texture coordinates
     */
    EXPORT inline Math::Vector2f PixelToTextureScale(const Math::Vector2f& coordinates, float textureSize)
    {
        return coordinates / textureSize;
    }
}

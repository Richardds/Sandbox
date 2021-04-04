// ----------------------------------------------------------------------------------------
//  \file       SkyboxGenerator.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Singleton.h"
#include "Util/Generators/Generator.h"

namespace Util
{
    /// Generates 2D glyph mesh
    class GlyphMeshGenerator : public Generator
    {
    _Singleton(GlyphMeshGenerator)

    public:
        GlyphMeshGenerator();

        [[nodiscard]] std::shared_ptr<Graphics::Mesh> Generate(float width,
                                                               float height,
                                                               const Math::Vector2f& offset);

    private:
        Graphics::VertexAttributeConfig _glyphAttributesTemplate;
    };
}

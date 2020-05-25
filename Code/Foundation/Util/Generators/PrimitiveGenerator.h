// ----------------------------------------------------------------------------------------
//  \file       PrimitiveGenerator.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Singleton.h"
#include "Util/Generators/Generator.h"

namespace Util
{
    /// Generates 2D and 3D quads by given size
    class PrimitiveGenerator : public Generator
    {
    _Singleton(PrimitiveGenerator)

    public:
        PrimitiveGenerator();
        [[nodiscard]] std::shared_ptr<Graphics::Mesh> Generate2dQuad(float size);
        [[nodiscard]] std::shared_ptr<Graphics::Mesh> Generate3dQuad(float size);

    private:
        Graphics::VertexAttributeConfig _2dQuadAttributesTemplate;
        Graphics::VertexAttributeConfig _3dQuadAttributesTemplate;
    };
}

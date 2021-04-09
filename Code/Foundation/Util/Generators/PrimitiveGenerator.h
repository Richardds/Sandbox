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
    /// Generates 2D and 3D primitives
    class EXPORT PrimitiveGenerator : public Generator
    {
    _Singleton(PrimitiveGenerator)

    public:
        PrimitiveGenerator();
        virtual ~PrimitiveGenerator() = default;

        std::shared_ptr<Graphics::Mesh> Generate2dQuad(float diameter);
        std::shared_ptr<Graphics::Mesh> Generate3dQuad(float diameter);

    private:
        Graphics::VertexAttributeConfig _2dAttributesTemplate;
        Graphics::VertexAttributeConfig _3dAttributesTemplate;
    };
}

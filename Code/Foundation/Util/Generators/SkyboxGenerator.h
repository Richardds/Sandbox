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
    /// Generates 3D skybox cube
    class EXPORT SkyboxGenerator : public Generator
    {
    _Singleton(SkyboxGenerator)

    public:
        SkyboxGenerator();
        virtual ~SkyboxGenerator() = default;

        std::shared_ptr<Graphics::Mesh> Generate(float size);

    private:
        Graphics::VertexAttributeConfig _skyboxAttributesTemplate;
    };
}

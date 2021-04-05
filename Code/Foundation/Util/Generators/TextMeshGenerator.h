// ----------------------------------------------------------------------------------------
//  \file       SkyboxGenerator.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Singleton.h"
#include "Graphics/Font.h"
#include "Graphics/Text.h"
#include "Util/Generators/Generator.h"

namespace Util
{
    /// Generates 2D text mesh
    class TextMeshGenerator : public Generator
    {
    _Singleton(TextMeshGenerator)

    public:
        TextMeshGenerator();

        [[nodiscard]] std::shared_ptr<Graphics::Text> Generate(const std::string& text,
                                                               const std::shared_ptr<Graphics::Font>& font) const;

    private:
        Graphics::VertexAttributeConfig _characterAttributesTemplate;
    };
}
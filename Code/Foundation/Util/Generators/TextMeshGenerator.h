// ----------------------------------------------------------------------------------------
//  \file       SkyboxGenerator.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Singleton.h"
#include "Graphics/TextType.h"
#include "Graphics/Text.h"
#include "Util/Generators/Generator.h"

namespace Util
{
    /// Generates 2D glyph mesh
    class TextMeshGenerator : public Generator
    {
    _Singleton(TextMeshGenerator)

    public:
        TextMeshGenerator();

        [[nodiscard]] std::shared_ptr<Graphics::Text> Generate(const std::string& text,
                                                               const std::shared_ptr<Graphics::TextType>& textType,
                                                               float size) const;

    private:
        Graphics::VertexAttributeConfig _characterAttributesTemplate;
    };
}

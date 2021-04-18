// ----------------------------------------------------------------------------------------
//  \file       SkyboxGenerator.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/Font.h"
#include "Graphics/Text.h"
#include "Util/Generators/Generator.h"

namespace Util
{
    /// Generates 2D text mesh
    class EXPORT TextMeshGenerator final : public Generator
    {
    public:
        TextMeshGenerator(const std::shared_ptr<Graphics::Font>& font, float spacingScale = 1.0f);

        std::shared_ptr<Graphics::Mesh> GenerateMesh(const std::basic_string<Character>& text) const;
        std::shared_ptr<Graphics::Text> Generate(const std::basic_string<Character>& text) const;

    private:
        Math::Vector2f CalculateTextMeshSize(const std::basic_string<Character>& text) const;

        Graphics::VertexAttributeConfig _characterAttributesTemplate;
        std::shared_ptr<Graphics::Font> _font;
        float _spacingScale;
    };
}

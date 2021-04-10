// ----------------------------------------------------------------------------------------
//  \file       SkyboxGenerator.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
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
    class EXPORT TextMeshGenerator : public Generator
    {
    _Singleton(TextMeshGenerator)

    public:
        TextMeshGenerator();
        virtual ~TextMeshGenerator() = default;

        std::shared_ptr<Graphics::Text> Generate(const std::basic_string<Character>& text,
                                                 const std::shared_ptr<Graphics::Font>& font,
                                                 float spacingScale = 1.0f) const;

    private:
        Graphics::VertexAttributeConfig _characterAttributesTemplate;

        Math::Vector2f CalculateTextMeshSize(const std::basic_string<Character>& text,
                                             const std::shared_ptr<Graphics::Font>& font,
                                             float spacingScale) const;
    };
}

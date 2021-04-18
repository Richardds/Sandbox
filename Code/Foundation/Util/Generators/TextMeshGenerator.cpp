// ----------------------------------------------------------------------------------------
//  \file       SkyboxGenerator.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Util/Generators/TextMeshGenerator.h"
#include "Graphics/GraphicsUtils.h"
#include "Core/Types.h"
#include "Math/MathUtils.h"

Util::TextMeshGenerator::TextMeshGenerator(const std::shared_ptr<Graphics::Font>& font, const float spacingScale) :
    _font(font),
    _spacingScale(spacingScale)
{
    this->_characterAttributesTemplate.Append(GL_FLOAT, 2);
    this->_characterAttributesTemplate.Append(GL_FLOAT, 2);
}

std::shared_ptr<Graphics::Text> Util::TextMeshGenerator::Generate(const std::basic_string<Character>& text) const
{
    _Assert(this->_font->GetState() == Graphics::Font::State::Loaded)

    const std::shared_ptr<Graphics::Texture>& fontMap = this->_font->GetFontMap();
    const float textureSize = static_cast<float>(fontMap->GetWidth());

    // Calculate offset by mesh width
    const Math::Vector2f meshSize = this->CalculateTextMeshSize(text);

    Math::Vector2f offset(meshSize / -2.0f);
    std::vector<Graphics::VertexData2> vertices;
    std::vector<uint32_t> indices;

    // Reserve known count of vertices and indices
    const size_t characterCount = text.size();
    vertices.reserve(characterCount * 4); // 4 vertices per character
    indices.reserve(characterCount * 6);  // 6 indices per character

    // Indices counter
    uint32_t ic = 0;

    for (const Character character : text)
    {
        // Retrieve the current character's properties from font
        const auto& [mapping, positioning] = this->_font->GetCharacterProperties(character);

        // NDC offset
        const Math::Vector2f ndcOffsetScale = Graphics::PixelToNDCScale(offset + positioning.offset);
        const Math::Vector2f ndcOffset = Math::Vector2f(ndcOffsetScale.x, -ndcOffsetScale.y);
        // NDC
        const Math::Vector2f ndcScale = Graphics::PixelToNDCScale(Math::Vector2f(mapping.width, mapping.height));

        // Texture offset
        const Math::Vector2f texOffset = Graphics::PixelToTextureScale(mapping.offset, textureSize);
        // Texture
        const Math::Vector2f texScale = Graphics::PixelToTextureScale(Math::Vector2f(mapping.width, mapping.height), textureSize);

        // Append character vertex data
        const std::vector<Graphics::VertexData2> characterVertexData({
            {ndcOffset.x,              ndcOffset.y - ndcScale.y, texOffset.x,              texOffset.y + texScale.y},
            {ndcOffset.x + ndcScale.x, ndcOffset.y - ndcScale.y, texOffset.x + texScale.x, texOffset.y + texScale.y},
            {ndcOffset.x + ndcScale.x, ndcOffset.y,              texOffset.x + texScale.x, texOffset.y},
            {ndcOffset.x,              ndcOffset.y,              texOffset.x,              texOffset.y}
        });
        vertices.insert(vertices.end(), characterVertexData.begin(), characterVertexData.end());

        // Append character indices
        const std::vector<uint32_t> characterElements({
            ic,     ic + 1, ic + 3,
            ic + 1, ic + 2, ic + 3
        });
        indices.insert(indices.end(), characterElements.begin(), characterElements.end());
        ic += 4;

        // Update cursor
        offset.x += positioning.advance - this->_font->GetSpacing() * _spacingScale;
        //offset.y += 0.0f; // TODO: Replace by line height on new line
    }

    std::shared_ptr<Graphics::Mesh> textMesh = this->Store(vertices, indices, this->_characterAttributesTemplate);

    return std::make_shared<Graphics::Text>(textMesh, fontMap);
}

Math::Vector2f Util::TextMeshGenerator::CalculateTextMeshSize(const std::basic_string<Character>& text) const
{
    Math::Vector2f size(0.0f);

    for (const Character character : text)
    {
        // Retrieve the current character's properties from font
        const auto& [mapping, positioning] = this->_font->GetCharacterProperties(character);

        size.x += positioning.advance - this->_font->GetSpacing() * this->_spacingScale;
        size.y = Math::Max(mapping.height, size.y);
    }

    return size;
}

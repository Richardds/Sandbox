// ----------------------------------------------------------------------------------------
//  \file       SkyboxGenerator.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Util/Generators/TextMeshGenerator.h"
#include "Graphics/GraphicsUtils.h"
#include "Core/Types.h"

Util::TextMeshGenerator::TextMeshGenerator()
{
    this->_characterAttributesTemplate.Append(GL_FLOAT, 2);
    this->_characterAttributesTemplate.Append(GL_FLOAT, 2);
}

std::shared_ptr<Graphics::Text> Util::TextMeshGenerator::Generate(const std::string& text,
                                                                  const std::shared_ptr<Graphics::Font>& textType) const
{
    const std::shared_ptr<Graphics::Texture>& fontMap = textType->GetFontMap();
    const float textureSize = static_cast<float>(fontMap->GetWidth());

    Math::Vector2f offset(0.0f);
    std::vector<Graphics::VertexData2> vertices;
    std::vector<uint32_t> indices;

    // Reserve known count of vertices and indices
    const size_t characterCount = text.size();
    vertices.reserve(characterCount * 4); // 4 vertices per character
    indices.reserve(characterCount * 6);  // 6 indices per character

    // Indices counter
    uint32_t ic = 0;

    for (const char character : text)
    {
        // Retrieve mapping from text type
        const Graphics::Font::CharacterMapping& mapping = textType->GetCharacterMapping(character);

        // NDC
        const Math::Vector2f ndcScale = Graphics::PixelToNDCScale(Math::Vector2f(mapping.width, mapping.height));
        // NDC offset
        const Math::Vector2f ndcOffsetScale = Graphics::PixelToNDCScale(offset);
        const Math::Vector2f ndcOffset = Math::Vector2f(-1.0f, 1.0f) + Math::Vector2f(ndcOffsetScale.x, -ndcOffsetScale.y);

        // Texture
        const Math::Vector2f texScale = Graphics::PixelToTextureScale(Math::Vector2f(mapping.width, mapping.height), textureSize);
        // Texture offset
        const Math::Vector2f texOffset = Graphics::PixelToTextureScale(mapping.offset, textureSize);

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
        offset.x += mapping.width;
        //offset.y += 0.0f; // TODO: Replace by line height on new line
    }

    std::shared_ptr<Graphics::Mesh> textMesh = this->Store(vertices, indices, this->_characterAttributesTemplate);

    return std::make_shared<Graphics::Text>(textMesh, fontMap);
}

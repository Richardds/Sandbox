// ----------------------------------------------------------------------------------------
//  \file       SkyboxGenerator.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Util/Generators/GlyphMeshGenerator.h"
#include "Graphics/GraphicsUtils.h"
#include "Core/Types.h"

Util::GlyphMeshGenerator::GlyphMeshGenerator()
{
    this->_glyphAttributesTemplate.Append(GL_FLOAT, 2);
    this->_glyphAttributesTemplate.Append(GL_FLOAT, 2);
}

std::shared_ptr<Graphics::Mesh> Util::GlyphMeshGenerator::Generate(const float width, const float height, const Math::Vector2f& offset)
{
    const Math::Vector2f ndcOffset = Math::Vector2f(-1.0f, 1.0f) + Graphics::PixelToNDCScale(offset);
    const Math::Vector2f ndc = Graphics::PixelToNDCScale(Math::Vector2f(width, height));



    const std::vector<VertexData2> vertexData({
        {ndcOffset.x,         ndcOffset.y - ndc.y, 0.0f, 1.0f},
        {ndcOffset.x + ndc.x, ndcOffset.y - ndc.y, 1.0f, 1.0f},
        {ndcOffset.x + ndc.x, ndcOffset.y,         1.0f, 0.0f},
        {ndcOffset.x,         ndcOffset.y,         0.0f, 0.0f}
    });

    const std::vector<uint32_t> elements({
        0, 1, 3,
        1, 2, 3
    });

    return this->Store(vertexData, elements, this->_glyphAttributesTemplate);
}

// ----------------------------------------------------------------------------------------
//  \file       PrimitiveGenerator.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Util/Generators/PrimitiveGenerator.h"
#include "Core/Types.h"

Util::PrimitiveGenerator::PrimitiveGenerator()
{
    this->_2dAttributesTemplate.Append(GL_FLOAT, 2);
    this->_2dAttributesTemplate.Append(GL_FLOAT, 2);

    this->_3dAttributesTemplate.Append(GL_FLOAT, 3);
    this->_3dAttributesTemplate.Append(GL_FLOAT, 3);
    this->_3dAttributesTemplate.Append(GL_FLOAT, 2);
    this->_3dAttributesTemplate.Append(GL_FLOAT, 3);
}

std::shared_ptr<Graphics::Mesh> Util::PrimitiveGenerator::Generate2dQuad(const float size)
{
    const std::vector<VertexData2> vertexData({
        {-size, -size, 0.0f, 0.0f},
        {size, -size, 1.0f, 0.0f},
        {size, size, 1.0f, 1.0f},
        {-size, size, 0.0f, 1.0f}
    });

    const std::vector<uint32_t> elements({
        0, 1, 3,
        1, 2, 3
    });

    return this->Store(vertexData, elements, this->_2dAttributesTemplate);
}

std::shared_ptr<Graphics::Mesh> Util::PrimitiveGenerator::Generate3dQuad(const float size)
{
    const std::vector<VertexData3> vertexData({
        {
            -size, 0.0f, size,
             0.0f, 1.0f, 0.0f,
             0.0f, 1.0f,
             1.0f, 0.0f, 0.0f
        },
        {
            size, 0.0f, size,
            0.0f, 1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 0.0f, 0.0f
        },
        {
            size, -0.0f, -size,
            0.0f,  1.0f,  0.0f,
            1.0f,  0.0f,
            1.0f,  0.0f,  0.0f
        },
        {
            -size, -0.0f, -size,
             0.0f,  1.0f,  0.0f,
             0.0f,  0.0f,
             1.0f,  0.0f,  0.0f
        }
    });

    const std::vector<uint32_t> elements({
        0, 1, 2,
        0, 2, 3
    });

    return this->Store(vertexData, elements, this->_3dAttributesTemplate);
}

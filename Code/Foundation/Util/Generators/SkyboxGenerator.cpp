// ----------------------------------------------------------------------------------------
//  \file       SkyboxGenerator.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Util/Generators/SkyboxGenerator.h"
#include "Math/Vector.h"

Util::SkyboxGenerator::SkyboxGenerator()
{
    this->_skyboxAttributesTemplate.Append(GL_FLOAT, 3);
}

std::shared_ptr<Graphics::Mesh> Util::SkyboxGenerator::Generate(const float size) const
{
    const float radius = size / 2.0f;

    const std::vector<Math::Vector3f> vertices({
        Math::Vector3f(-radius, radius, -radius),
        Math::Vector3f(-radius, -radius, -radius),
        Math::Vector3f(radius, -radius, -radius),
        Math::Vector3f(radius, radius, -radius),

        Math::Vector3f(-radius, radius, radius),
        Math::Vector3f(-radius, -radius, radius),
        Math::Vector3f(radius, -radius, radius),
        Math::Vector3f(radius, radius, radius)
    });

    const std::vector<uint32_t> indices({
        0, 1, 3,
        3, 1, 2,

        1, 5, 2,
        2, 5, 6,

        5, 4, 6,
        6, 4, 7,

        4, 0, 7,
        7, 0, 3,

        3, 2, 7,
        7, 2, 6,

        4, 5, 0,
        0, 5, 1
    });

    return this->Store(vertices, indices, this->_skyboxAttributesTemplate);
}

// ----------------------------------------------------------------------------------------
//  \file       Hardcoded.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include <Precompiled.h>

#include "Game/Scene/Hardcoded.h"
#include "Core/Types.h"

Sandbox::Hardcoded::Hardcoded()
{
    this->_hardcodedAttributesTemplate.Append(GL_FLOAT, 3);
    this->_hardcodedAttributesTemplate.Append(GL_FLOAT, 3);
    this->_hardcodedAttributesTemplate.Append(GL_FLOAT, 2);
    this->_hardcodedAttributesTemplate.Append(GL_FLOAT, 3);
}

std::shared_ptr<Graphics::Mesh> Sandbox::Hardcoded::Generate()
{
    const std::vector<VertexData3> vertexData({
        {
            0.000000f, 0.750000f, -0.000000f, 0.192450f, 0.962250f, -0.192450f, 0.750000f, 0.375000f, -0.955778f,
            0.228246f, 0.185450f
        },
        {
            -1.000000f, 1.000000f, -0.000000f, 0.192450f, 0.962250f, -0.192450f, 0.875000f, 0.375000f, -0.980194f,
            0.197837f, 0.008993f
        },
        {
            -1.250000f, 1.250000f, 1.250000f, 0.192450f, 0.962250f, -0.192450f, 0.875000f, 0.250000f, -0.955778f,
            0.228246f, 0.185450f
        },
        {
            0.000000f, 1.000000f, 1.000000f, 0.192450f, 0.962250f, -0.192450f, 0.750000f, 0.250000f, -0.955778f,
            0.228246f, 0.185450f
        },
        {
            0.000000f, 0.000000f, 0.750000f, 0.192450f, -0.192450f, 0.962250f, 0.500000f, 0.125000f, -0.185450f,
            0.955778f, 0.228246f
        },
        {
            0.000000f, 1.000000f, 1.000000f, 0.192450f, -0.192450f, 0.962250f, 0.625000f, 0.125000f, -0.008993f,
            0.980194f, 0.197837f
        },
        {
            -1.250000f, 1.250000f, 1.250000f, 0.192450f, -0.192450f, 0.962250f, 0.625000f, 0.000000f, -0.185450f,
            0.955778f, 0.228246f
        },
        {
            -1.000000f, 0.000000f, 1.000000f, 0.192450f, -0.192450f, 0.962250f, 0.500000f, 0.000000f, -0.185450f,
            0.955778f, 0.228246f
        },
        {
            -0.750000f, 0.000000f, 0.000000f, -0.962250f, -0.192450f, 0.192450f, 0.500000f, 0.875000f, -0.228246f,
            0.955778f, -0.185450f
        },
        {
            -1.000000f, 1.000000f, -0.000000f, -0.962250f, -0.192450f, 0.192450f, 0.625000f, 0.875000f, -0.197837f,
            0.980194f, -0.008993f
        },
        {
            -1.250000f, 1.250000f, -1.250000f, -0.962250f, -0.192450f, 0.192450f, 0.625000f, 0.750000f, -0.228246f,
            0.955778f, -0.185450f
        },
        {
            -1.000000f, -0.000000f, -1.000000f, -0.962250f, -0.192450f, 0.192450f, 0.500000f, 0.750000f, -0.228246f,
            0.955778f, -0.185450f
        },
        {
            0.000000f, -0.750000f, 0.000000f, -0.192450f, -0.962250f, -0.192450f, 0.250000f, 0.375000f, 0.955778f,
            -0.228246f, 0.185450f
        },
        {
            1.000000f, -1.000000f, 0.000000f, -0.192450f, -0.962250f, -0.192450f, 0.375000f, 0.375000f, 0.980194f,
            -0.197837f, 0.008993f
        },
        {
            1.250000f, -1.250000f, 1.250000f, -0.192450f, -0.962250f, -0.192450f, 0.375000f, 0.250000f, 0.955778f,
            -0.228246f, 0.185450f
        },
        {
            0.000000f, -1.000000f, 1.000000f, -0.192450f, -0.962250f, -0.192450f, 0.250000f, 0.250000f, 0.955778f,
            -0.228246f, 0.185450f
        },
        {
            0.750000f, 0.000000f, 0.000000f, 0.962250f, -0.192450f, -0.192450f, 0.500000f, 0.375000f, 0.228246f,
            0.955778f, 0.185450f
        },
        {
            1.000000f, 1.000000f, -0.000000f, 0.962250f, -0.192450f, -0.192450f, 0.625000f, 0.375000f, 0.197837f,
            0.980194f, 0.008993f
        },
        {
            1.250000f, 1.250000f, 1.250000f, 0.962250f, -0.192450f, -0.192450f, 0.625000f, 0.250000f, 0.228246f,
            0.955778f, 0.185450f
        },
        {
            1.000000f, 0.000000f, 1.000000f, 0.962250f, -0.192450f, -0.192450f, 0.500000f, 0.250000f, 0.228246f,
            0.955778f, 0.185450f
        },
        {
            0.000000f, -0.000000f, -0.750000f, -0.192450f, -0.192450f, -0.962250f, 0.500000f, 0.625000f, 0.185450f,
            0.955778f, -0.228246f
        },
        {
            0.000000f, 1.000000f, -1.000000f, -0.192450f, -0.192450f, -0.962250f, 0.625000f, 0.625000f, 0.008993f,
            0.980194f, -0.197837f
        },
        {
            1.250000f, 1.250000f, -1.250000f, -0.192450f, -0.192450f, -0.962250f, 0.625000f, 0.500000f, 0.185450f,
            0.955778f, -0.228246f
        },
        {
            1.000000f, -0.000000f, -1.000000f, -0.192450f, -0.192450f, -0.962250f, 0.500000f, 0.500000f, 0.185450f,
            0.955778f, -0.228246f
        },
        {
            0.000000f, -1.000000f, -1.000000f, -0.192450f, 0.192450f, -0.962250f, 0.375000f, 0.625000f, -0.185450f,
            0.955778f, 0.228246f
        },
        {
            0.000000f, -0.000000f, -0.750000f, -0.192450f, 0.192450f, -0.962250f, 0.500000f, 0.625000f, -0.008993f,
            0.980194f, 0.197837f
        },
        {
            1.000000f, -0.000000f, -1.000000f, -0.192450f, 0.192450f, -0.962250f, 0.500000f, 0.500000f, -0.185450f,
            0.955778f, 0.228246f
        },
        {
            1.250000f, -1.250000f, -1.250000f, -0.192450f, 0.192450f, -0.962250f, 0.375000f, 0.500000f, -0.185450f,
            0.955778f, 0.228246f
        },
        {
            -1.250000f, -1.250000f, -1.250000f, 0.192450f, 0.192450f, -0.962250f, 0.375000f, 0.750000f, 0.008993f,
            0.980194f, 0.197837f
        },
        {
            -1.000000f, -0.000000f, -1.000000f, 0.192450f, 0.192450f, -0.962250f, 0.500000f, 0.750000f, 0.185450f,
            0.955778f, 0.228246f
        },
        {
            0.000000f, -0.000000f, -0.750000f, 0.192450f, 0.192450f, -0.962250f, 0.500000f, 0.625000f, 0.008993f,
            0.980194f, 0.197837f
        },
        {
            0.000000f, -1.000000f, -1.000000f, 0.192450f, 0.192450f, -0.962250f, 0.375000f, 0.625000f, 0.008993f,
            0.980194f, 0.197837f
        },
        {
            -1.000000f, -0.000000f, -1.000000f, 0.192450f, -0.192450f, -0.962250f, 0.500000f, 0.750000f, -0.008993f,
            0.980194f, -0.197837f
        },
        {
            -1.250000f, 1.250000f, -1.250000f, 0.192450f, -0.192450f, -0.962250f, 0.625000f, 0.750000f, -0.185450f,
            0.955778f, -0.228246f
        },
        {
            0.000000f, 1.000000f, -1.000000f, 0.192450f, -0.192450f, -0.962250f, 0.625000f, 0.625000f, -0.008993f,
            0.980194f, -0.197837f
        },
        {
            0.000000f, -0.000000f, -0.750000f, 0.192450f, -0.192450f, -0.962250f, 0.500000f, 0.625000f, -0.008993f,
            0.980194f, -0.197837f
        },
        {
            1.000000f, -1.000000f, 0.000000f, 0.962250f, 0.192450f, -0.192450f, 0.375000f, 0.375000f, -0.228246f,
            0.955778f, -0.185450f
        },
        {
            0.750000f, 0.000000f, 0.000000f, 0.962250f, 0.192450f, -0.192450f, 0.500000f, 0.375000f, -0.197837f,
            0.980194f, -0.008993f
        },
        {
            1.000000f, 0.000000f, 1.000000f, 0.962250f, 0.192450f, -0.192450f, 0.500000f, 0.250000f, -0.228246f,
            0.955778f, -0.185450f
        },
        {
            1.250000f, -1.250000f, 1.250000f, 0.962250f, 0.192450f, -0.192450f, 0.375000f, 0.250000f, -0.228246f,
            0.955778f, -0.185450f
        },
        {
            1.250000f, -1.250000f, -1.250000f, 0.962250f, 0.192450f, 0.192450f, 0.375000f, 0.500000f, -0.197837f,
            0.980194f, 0.008993f
        },
        {
            1.000000f, -0.000000f, -1.000000f, 0.962250f, 0.192450f, 0.192450f, 0.500000f, 0.500000f, -0.228246f,
            0.955778f, 0.185450f
        },
        {
            0.750000f, 0.000000f, 0.000000f, 0.962250f, 0.192450f, 0.192450f, 0.500000f, 0.375000f, -0.197837f,
            0.980194f, 0.008993f
        },
        {
            1.000000f, -1.000000f, 0.000000f, 0.962250f, 0.192450f, 0.192450f, 0.375000f, 0.375000f, -0.197837f,
            0.980194f, 0.008993f
        },
        {
            1.000000f, -0.000000f, -1.000000f, 0.962250f, -0.192450f, 0.192450f, 0.500000f, 0.500000f, 0.197837f,
            0.980194f, -0.008993f
        },
        {
            1.250000f, 1.250000f, -1.250000f, 0.962250f, -0.192450f, 0.192450f, 0.625000f, 0.500000f, 0.228246f,
            0.955778f, -0.185450f
        },
        {
            1.000000f, 1.000000f, -0.000000f, 0.962250f, -0.192450f, 0.192450f, 0.625000f, 0.375000f, 0.197837f,
            0.980194f, -0.008993f
        },
        {
            0.750000f, 0.000000f, 0.000000f, 0.962250f, -0.192450f, 0.192450f, 0.500000f, 0.375000f, 0.197837f,
            0.980194f, -0.008993f
        },
        {
            -1.000000f, -1.000000f, 0.000000f, 0.192450f, -0.962250f, -0.192450f, 0.125000f, 0.375000f, 0.955778f,
            0.228246f, -0.185450f
        },
        {
            0.000000f, -0.750000f, 0.000000f, 0.192450f, -0.962250f, -0.192450f, 0.250000f, 0.375000f, 0.980194f,
            0.197837f, -0.008993f
        },
        {
            0.000000f, -1.000000f, 1.000000f, 0.192450f, -0.962250f, -0.192450f, 0.250000f, 0.250000f, 0.955778f,
            0.228246f, -0.185450f
        },
        {
            -1.250000f, -1.250000f, 1.250000f, 0.192450f, -0.962250f, -0.192450f, 0.125000f, 0.250000f, 0.955778f,
            0.228246f, -0.185450f
        },
        {
            -1.250000f, -1.250000f, -1.250000f, 0.192450f, -0.962250f, 0.192450f, 0.125000f, 0.500000f, 0.980194f,
            0.197837f, 0.008993f
        },
        {
            0.000000f, -1.000000f, -1.000000f, 0.192450f, -0.962250f, 0.192450f, 0.250000f, 0.500000f, 0.955778f,
            0.228246f, 0.185450f
        },
        {
            0.000000f, -0.750000f, 0.000000f, 0.192450f, -0.962250f, 0.192450f, 0.250000f, 0.375000f, 0.980194f,
            0.197837f, 0.008993f
        },
        {
            -1.000000f, -1.000000f, 0.000000f, 0.192450f, -0.962250f, 0.192450f, 0.125000f, 0.375000f, 0.980194f,
            0.197837f, 0.008993f
        },
        {
            0.000000f, -1.000000f, -1.000000f, -0.192450f, -0.962250f, 0.192450f, 0.250000f, 0.500000f, 0.980194f,
            -0.197837f, -0.008993f
        },
        {
            1.250000f, -1.250000f, -1.250000f, -0.192450f, -0.962250f, 0.192450f, 0.375000f, 0.500000f, 0.955778f,
            -0.228246f, -0.185450f
        },
        {
            1.000000f, -1.000000f, 0.000000f, -0.192450f, -0.962250f, 0.192450f, 0.375000f, 0.375000f, 0.980194f,
            -0.197837f, -0.008993f
        },
        {
            0.000000f, -0.750000f, 0.000000f, -0.192450f, -0.962250f, 0.192450f, 0.250000f, 0.375000f, 0.980194f,
            -0.197837f, -0.008993f
        },
        {
            -1.000000f, -1.000000f, 0.000000f, -0.962250f, 0.192450f, 0.192450f, 0.375000f, 0.875000f, 0.228246f,
            0.955778f, 0.185450f
        },
        {
            -0.750000f, 0.000000f, 0.000000f, -0.962250f, 0.192450f, 0.192450f, 0.500000f, 0.875000f, 0.197837f,
            0.980194f, 0.008993f
        },
        {
            -1.000000f, -0.000000f, -1.000000f, -0.962250f, 0.192450f, 0.192450f, 0.500000f, 0.750000f, 0.228246f,
            0.955778f, 0.185450f
        },
        {
            -1.250000f, -1.250000f, -1.250000f, -0.962250f, 0.192450f, 0.192450f, 0.375000f, 0.750000f, 0.228246f,
            0.955778f, 0.185450f
        },
        {
            -1.250000f, -1.250000f, 1.250000f, -0.962250f, 0.192450f, -0.192450f, 0.375000f, 1.000000f, 0.197837f,
            0.980194f, -0.008993f
        },
        {
            -1.000000f, 0.000000f, 1.000000f, -0.962250f, 0.192450f, -0.192450f, 0.500000f, 1.000000f, 0.228246f,
            0.955778f, -0.185450f
        },
        {
            -0.750000f, 0.000000f, 0.000000f, -0.962250f, 0.192450f, -0.192450f, 0.500000f, 0.875000f, 0.197837f,
            0.980194f, -0.008993f
        },
        {
            -1.000000f, -1.000000f, 0.000000f, -0.962250f, 0.192450f, -0.192450f, 0.375000f, 0.875000f, 0.197837f,
            0.980194f, -0.008993f
        },
        {
            -1.000000f, 0.000000f, 1.000000f, -0.962250f, -0.192450f, -0.192450f, 0.500000f, 1.000000f, -0.197837f,
            0.980194f, 0.008993f
        },
        {
            -1.250000f, 1.250000f, 1.250000f, -0.962250f, -0.192450f, -0.192450f, 0.625000f, 1.000000f, -0.228246f,
            0.955778f, 0.185450f
        },
        {
            -1.000000f, 1.000000f, -0.000000f, -0.962250f, -0.192450f, -0.192450f, 0.625000f, 0.875000f, -0.197837f,
            0.980194f, 0.008993f
        },
        {
            -0.750000f, 0.000000f, 0.000000f, -0.962250f, -0.192450f, -0.192450f, 0.500000f, 0.875000f, -0.197837f,
            0.980194f, 0.008993f
        },
        {
            0.000000f, -1.000000f, 1.000000f, 0.192450f, 0.192450f, 0.962250f, 0.375000f, 0.125000f, 0.185450f,
            0.955778f, -0.228246f
        },
        {
            0.000000f, 0.000000f, 0.750000f, 0.192450f, 0.192450f, 0.962250f, 0.500000f, 0.125000f, 0.008993f,
            0.980194f, -0.197837f
        },
        {
            -1.000000f, 0.000000f, 1.000000f, 0.192450f, 0.192450f, 0.962250f, 0.500000f, 0.000000f, 0.185450f,
            0.955778f, -0.228246f
        },
        {
            -1.250000f, -1.250000f, 1.250000f, 0.192450f, 0.192450f, 0.962250f, 0.375000f, 0.000000f, 0.185450f,
            0.955778f, -0.228246f
        },
        {
            1.250000f, -1.250000f, 1.250000f, -0.192450f, 0.192450f, 0.962250f, 0.375000f, 0.250000f, -0.008993f,
            0.980194f, -0.197837f
        },
        {
            1.000000f, 0.000000f, 1.000000f, -0.192450f, 0.192450f, 0.962250f, 0.500000f, 0.250000f, -0.185450f,
            0.955778f, -0.228246f
        },
        {
            0.000000f, 0.000000f, 0.750000f, -0.192450f, 0.192450f, 0.962250f, 0.500000f, 0.125000f, -0.008993f,
            0.980194f, -0.197837f
        },
        {
            0.000000f, -1.000000f, 1.000000f, -0.192450f, 0.192450f, 0.962250f, 0.375000f, 0.125000f, -0.008993f,
            0.980194f, -0.197837f
        },
        {
            1.000000f, 0.000000f, 1.000000f, -0.192450f, -0.192450f, 0.962250f, 0.500000f, 0.250000f, 0.008993f,
            0.980194f, 0.197837f
        },
        {
            1.250000f, 1.250000f, 1.250000f, -0.192450f, -0.192450f, 0.962250f, 0.625000f, 0.250000f, 0.185450f,
            0.955778f, 0.228246f
        },
        {
            0.000000f, 1.000000f, 1.000000f, -0.192450f, -0.192450f, 0.962250f, 0.625000f, 0.125000f, 0.008993f,
            0.980194f, 0.197837f
        },
        {
            0.000000f, 0.000000f, 0.750000f, -0.192450f, -0.192450f, 0.962250f, 0.500000f, 0.125000f, 0.008993f,
            0.980194f, 0.197837f
        },
        {
            1.000000f, 1.000000f, -0.000000f, -0.192450f, 0.962250f, -0.192450f, 0.625000f, 0.375000f, -0.955778f,
            -0.228246f, -0.185450f
        },
        {
            0.000000f, 0.750000f, -0.000000f, -0.192450f, 0.962250f, -0.192450f, 0.750000f, 0.375000f, -0.980194f,
            -0.197837f, -0.008993f
        },
        {
            0.000000f, 1.000000f, 1.000000f, -0.192450f, 0.962250f, -0.192450f, 0.750000f, 0.250000f, -0.955778f,
            -0.228246f, -0.185450f
        },
        {
            1.250000f, 1.250000f, 1.250000f, -0.192450f, 0.962250f, -0.192450f, 0.625000f, 0.250000f, -0.955778f,
            -0.228246f, -0.185450f
        },
        {
            1.250000f, 1.250000f, -1.250000f, -0.192450f, 0.962250f, 0.192450f, 0.625000f, 0.500000f, -0.980194f,
            -0.197837f, 0.008993f
        },
        {
            0.000000f, 1.000000f, -1.000000f, -0.192450f, 0.962250f, 0.192450f, 0.750000f, 0.500000f, -0.955778f,
            -0.228246f, 0.185450f
        },
        {
            0.000000f, 0.750000f, -0.000000f, -0.192450f, 0.962250f, 0.192450f, 0.750000f, 0.375000f, -0.980194f,
            -0.197837f, 0.008993f
        },
        {
            1.000000f, 1.000000f, -0.000000f, -0.192450f, 0.962250f, 0.192450f, 0.625000f, 0.375000f, -0.980194f,
            -0.197837f, 0.008993f
        },
        {
            0.000000f, 1.000000f, -1.000000f, 0.192450f, 0.962250f, 0.192450f, 0.750000f, 0.500000f, -0.980194f,
            0.197837f, -0.008993f
        },
        {
            -1.250000f, 1.250000f, -1.250000f, 0.192450f, 0.962250f, 0.192450f, 0.875000f, 0.500000f, -0.955778f,
            0.228246f, -0.185450f
        },
        {
            -1.000000f, 1.000000f, -0.000000f, 0.192450f, 0.962250f, 0.192450f, 0.875000f, 0.375000f, -0.980194f,
            0.197837f, -0.008993f
        },
        {
            0.000000f, 0.750000f, -0.000000f, 0.192450f, 0.962250f, 0.192450f, 0.750000f, 0.375000f, -0.980194f,
            0.197837f, -0.008993f
        }
    });

    const std::vector<uint32_t> elements({
        0, 1, 2,
        0, 2, 3,
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11,
        12, 13, 14,
        12, 14, 15,
        16, 17, 18,
        16, 18, 19,
        20, 21, 22,
        20, 22, 23,
        24, 25, 26,
        24, 26, 27,
        28, 29, 30,
        28, 30, 31,
        32, 33, 34,
        32, 34, 35,
        36, 37, 38,
        36, 38, 39,
        40, 41, 42,
        40, 42, 43,
        44, 45, 46,
        44, 46, 47,
        48, 49, 50,
        48, 50, 51,
        52, 53, 54,
        52, 54, 55,
        56, 57, 58,
        56, 58, 59,
        60, 61, 62,
        60, 62, 63,
        64, 65, 66,
        64, 66, 67,
        68, 69, 70,
        68, 70, 71,
        72, 73, 74,
        72, 74, 75,
        76, 77, 78,
        76, 78, 79,
        80, 81, 82,
        80, 82, 83,
        84, 85, 86,
        84, 86, 87,
        88, 89, 90,
        88, 90, 91,
        92, 93, 94,
        92, 94, 95
    });

    return this->Store(vertexData, elements, this->_hardcodedAttributesTemplate);
}
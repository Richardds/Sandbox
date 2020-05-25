// ----------------------------------------------------------------------------------------
//  \file       VertexAttributeConfig.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/VertexArray.h"

namespace Graphics
{
    /// Helper class for initializing vertex attributes of a vertex array object
    class VertexAttributeConfig
    {
    public:
        struct VertexAttribute
        {
            GLenum type;
            uint16_t count;
            size_t size;
        };

        VertexAttributeConfig();
        void Append(GLenum type, uint16_t count);
        void Apply(const std::shared_ptr<VertexArray>& vao) const;

    private:
        size_t _size;
        std::vector<VertexAttribute> _attributes;
    };
}

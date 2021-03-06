// ----------------------------------------------------------------------------------------
//  \file       VertexAttributeConfig.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Graphics/VertexArray.h"

namespace Graphics
{
    /// Helper class for initializing vertex attributes of a vertex array object
    class EXPORT VertexAttributeConfig
    {
    public:
        struct VertexAttribute
        {
            GLenum type;
            uint16_t count;
            size_t size;
        };

        VertexAttributeConfig();
        virtual ~VertexAttributeConfig() = default;

        void Append(GLenum type, uint16_t count);
        void Apply(const std::shared_ptr<VertexArray>& vao) const;

    private:
        size_t _size;
        std::vector<VertexAttribute> _attributes;
    };
}

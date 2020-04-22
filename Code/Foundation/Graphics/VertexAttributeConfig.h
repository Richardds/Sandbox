#pragma once

#include <cstdint>
#include <vector>

#include "Core.h"
#include "VertexArray.h"

namespace Graphics
{

    class VertexAttributeConfig
    {
    public:
        struct VertexAttribute {
            GLenum type;
            uint16_t count;
            size_t size;
        };

        VertexAttributeConfig();
        virtual ~VertexAttributeConfig();
        void Append(GLenum type, uint16_t count, size_t elementSize);
        void Apply(std::shared_ptr<VertexArray> vao);

    private:
        size_t _size;
        std::vector<VertexAttribute> _attributes;
    };

}

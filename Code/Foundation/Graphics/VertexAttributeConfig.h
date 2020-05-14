#pragma once
#include <vector>

#include "../Core/Types.h"
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
        void Append(GLenum type, uint16_t count);
        void Apply(std::shared_ptr<VertexArray> vao) const;

    private:
        size_t _size;
        std::vector<VertexAttribute> _attributes;
    };

}

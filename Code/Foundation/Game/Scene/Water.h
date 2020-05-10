#pragma once

#include <memory>

#include "../Attributes/HasPosition.h"
#include "../../Graphics/Mesh.h"

namespace Graphics
{

    class Water : public HasPosition
    {
    public:
        Water(std::shared_ptr<Mesh> mesh);
        Water(std::shared_ptr<Mesh> mesh, Math::Vector3f position);
        virtual ~Water();
        std::shared_ptr<Mesh> GetMesh() const;
        void SetMesh(std::shared_ptr<Mesh> mesh);

    private:
        std::shared_ptr<Mesh> _mesh;
    };

    inline std::shared_ptr<Mesh> Graphics::Water::GetMesh() const
    {
        return this->_mesh;
    }

    inline void Graphics::Water::SetMesh(std::shared_ptr<Mesh> mesh)
    {
        this->_mesh = mesh;
    }

}

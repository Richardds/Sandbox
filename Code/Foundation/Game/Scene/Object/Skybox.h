// ----------------------------------------------------------------------------------------
//  \file       Skybox.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Graphics/Mesh.h"
#include "Graphics/Texture.h"

namespace Graphics
{
    /// 3D scene skybox
    class EXPORT Skybox
    {
    public:
        Skybox(const std::shared_ptr<Texture>& texture, float size);
        virtual ~Skybox() = default;

        std::shared_ptr<Mesh> GetMesh() const;
        void SetMesh(const std::shared_ptr<Mesh>& mesh);
        std::shared_ptr<Texture> GetTexture() const;
        void SetTexture(const std::shared_ptr<Texture>& texture);
        float GetSize() const;
        void Render() const;

    private:
        std::shared_ptr<Mesh> _mesh;
        std::shared_ptr<Texture> _texture;
        float _size;
    };

    inline std::shared_ptr<Mesh> Skybox::GetMesh() const
    {
        return this->_mesh;
    }

    inline void Skybox::SetMesh(const std::shared_ptr<Mesh>& mesh)
    {
        this->_mesh = mesh;
    }

    inline std::shared_ptr<Texture> Skybox::GetTexture() const
    {
        return this->_texture;
    }

    inline void Skybox::SetTexture(const std::shared_ptr<Texture>& texture)
    {
        _Assert(GL_TEXTURE_CUBE_MAP == texture->GetTarget())
        this->_texture = texture;
    }

    inline float Skybox::GetSize() const
    {
        return this->_size;
    }
}

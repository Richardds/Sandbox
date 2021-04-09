// ----------------------------------------------------------------------------------------
//  \file       TexturedMesh.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/Material.h"
#include "Graphics/Mesh.h"
#include "Graphics/Texture.h"
#include "Graphics/Shaders/EntityShader.h"

namespace Graphics
{
    /// Describes texture mapping attributes of a mesh
    class EXPORT TexturedMesh : public Mesh
    {
    public:
        TexturedMesh(const std::shared_ptr<VertexArray>& vertexArrayObject,
                     const std::shared_ptr<Buffer>& vertexBuffer,
                     const std::shared_ptr<Buffer>& elementsBuffer,
                     uint32_t elementsCount);
        explicit TexturedMesh(const std::shared_ptr<Mesh>& mesh);
        virtual ~TexturedMesh() = default;

        void Render(const std::shared_ptr<EntityShader>& shader) const;
        Material GetMaterial() const;
        void SetMaterial(const Material& material);
        bool HasDiffuseMap() const;
        std::shared_ptr<Texture> GetDiffuseMap() const;
        void SetDiffuseMap(const std::shared_ptr<Texture>& texture);
        bool HasNormalMap() const;
        std::shared_ptr<Texture> GetNormalMap() const;
        void SetNormalMap(const std::shared_ptr<Texture>& texture);
        bool HasSpecularMap() const;
        std::shared_ptr<Texture> GetSpecularMap() const;
        void SetSpecularMap(const std::shared_ptr<Texture>& texture);
        bool HasDistortionMap() const;
        std::shared_ptr<Texture> GetDistortionMap() const;
        void SetDistortionMap(const std::shared_ptr<Texture>& texture);

    private:
        Material _material;
        std::shared_ptr<Texture> _diffuseMap;
        std::shared_ptr<Texture> _normalMap;
        std::shared_ptr<Texture> _specularMap;
        std::shared_ptr<Texture> _distortionMap;
    };

    inline Material TexturedMesh::GetMaterial() const
    {
        return this->_material;
    }

    inline void TexturedMesh::SetMaterial(const Material& material)
    {
        this->_material = material;
    }

    inline bool TexturedMesh::HasDiffuseMap() const
    {
        return static_cast<bool>(this->_diffuseMap);
    }

    inline std::shared_ptr<Texture> TexturedMesh::GetDiffuseMap() const
    {
        return this->_diffuseMap;
    }

    inline void TexturedMesh::SetDiffuseMap(const std::shared_ptr<Texture>& texture)
    {
        _Assert(texture)
        _Assert(Texture::State::Loaded == texture->GetState())
        this->_diffuseMap = texture;
    }

    inline bool TexturedMesh::HasNormalMap() const
    {
        return static_cast<bool>(this->_normalMap);
    }

    inline std::shared_ptr<Texture> TexturedMesh::GetNormalMap() const
    {
        return this->_normalMap;
    }

    inline void TexturedMesh::SetNormalMap(const std::shared_ptr<Texture>& texture)
    {
        _Assert(texture)
        _Assert(Texture::State::Loaded == texture->GetState())
        this->_normalMap = texture;
    }

    inline bool TexturedMesh::HasSpecularMap() const
    {
        return static_cast<bool>(this->_specularMap);
    }

    inline std::shared_ptr<Texture> TexturedMesh::GetSpecularMap() const
    {
        return this->_specularMap;
    }

    inline void TexturedMesh::SetSpecularMap(const std::shared_ptr<Texture>& texture)
    {
        _Assert(texture)
        _Assert(Texture::State::Loaded == texture->GetState())
        this->_specularMap = texture;
    }

    inline bool TexturedMesh::HasDistortionMap() const
    {
        return static_cast<bool>(this->_distortionMap);
    }

    inline std::shared_ptr<Texture> TexturedMesh::GetDistortionMap() const
    {
        return this->_distortionMap;
    }

    inline void TexturedMesh::SetDistortionMap(const std::shared_ptr<Texture>& texture)
    {
        _Assert(texture)
        _Assert(Texture::State::Loaded == texture->GetState())
        this->_distortionMap = texture;
    }
}

#pragma once

#include "Mesh.h"
#include "Texture.h"

namespace Graphics
{

    class TexturedMesh : public Mesh
    {
    public:
        TexturedMesh(std::shared_ptr<Mesh> mesh);
        virtual ~TexturedMesh();
        void Render(std::shared_ptr<EntityShader> shader);
        bool HasDiffuseMap() const;
        std::shared_ptr<Graphics::Texture> GetDiffuseMap() const;
        void SetDiffuseMap(std::shared_ptr<Graphics::Texture> texture);
        bool HasNormalMap() const;
        std::shared_ptr<Graphics::Texture> GetNormalMap() const;
        void SetNormalMap(std::shared_ptr<Graphics::Texture> texture);
        bool HasSpecularMap() const;
        std::shared_ptr<Graphics::Texture> GetSpecularMap() const;
        void SetSpecularMap(std::shared_ptr<Graphics::Texture> texture);
        bool HasMaterialMap() const;
        std::shared_ptr<Graphics::Texture> GetMaterialMap() const;
        void SetMaterialMap(std::shared_ptr<Graphics::Texture> texture);

    private:
        std::shared_ptr<Graphics::Texture> _diffuseMap;
        std::shared_ptr<Graphics::Texture> _normalMap;
        std::shared_ptr<Graphics::Texture> _specularMap;
        std::shared_ptr<Graphics::Texture> _materialMap;
    };

    inline bool Graphics::TexturedMesh::HasDiffuseMap() const
    {
        return static_cast<bool>(this->_diffuseMap);
    }

    inline std::shared_ptr<Graphics::Texture> Graphics::TexturedMesh::GetDiffuseMap() const
    {
        return this->_diffuseMap;
    }

    inline void TexturedMesh::SetDiffuseMap(std::shared_ptr<Graphics::Texture> texture)
    {
        this->_diffuseMap = texture;
    }

    inline bool TexturedMesh::HasNormalMap() const
    {
        return static_cast<bool>(this->_normalMap);;
    }

    inline std::shared_ptr<Graphics::Texture> TexturedMesh::GetNormalMap() const
    {
        return this->_normalMap;
    }

    inline void TexturedMesh::SetNormalMap(std::shared_ptr<Graphics::Texture> texture)
    {
        this->_normalMap = texture;
    }

    inline bool TexturedMesh::HasSpecularMap() const
    {
        return static_cast<bool>(this->_specularMap);;
    }

    inline std::shared_ptr<Graphics::Texture> TexturedMesh::GetSpecularMap() const
    {
        return this->_specularMap;
    }

    inline void TexturedMesh::SetSpecularMap(std::shared_ptr<Graphics::Texture> texture)
    {
        this->_specularMap = texture;
    }

    inline bool TexturedMesh::HasMaterialMap() const
    {
        return static_cast<bool>(this->_materialMap);;
    }

    inline std::shared_ptr<Graphics::Texture> TexturedMesh::GetMaterialMap() const
    {
        return this->_materialMap;
    }

    inline void TexturedMesh::SetMaterialMap(std::shared_ptr<Graphics::Texture> texture)
    {
        this->_materialMap = texture;
    }

}

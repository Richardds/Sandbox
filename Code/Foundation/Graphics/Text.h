// ----------------------------------------------------------------------------------------
//  \file       TexturedMesh.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/Mesh.h"
#include "Graphics/Texture.h"
#include "Shaders/TextShader.h"

namespace Graphics
{
    class Text : public Mesh
    {
    public:
        Text(const std::shared_ptr<VertexArray>& vertexArrayObject,
             const std::shared_ptr<Buffer>& vertexBuffer,
             const std::shared_ptr<Buffer>& elementsBuffer,
             uint32_t elementsCount,
             const std::shared_ptr<Texture>& fontMap);
        Text(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Texture>& fontMap);

        void Render(const std::shared_ptr<TextShader>& shader) const;
        std::shared_ptr<Texture> GetFontMap() const;
        void SetFontMap(const std::shared_ptr<Texture>& texture);
        float GetSize() const;
        void SetSize(float size);
        Math::Vector4f GetColor() const;
        void SetColor(const Math::Vector4f& color);

    private:
        std::shared_ptr<Texture> _fontMap;
        float _size;
        Math::Vector4f _color;
    };
    
    inline std::shared_ptr<Texture> Text::GetFontMap() const
    {
        return this->_fontMap;
    }

    inline void Text::SetFontMap(const std::shared_ptr<Texture>& texture)
    {
        _Assert(texture)
        _Assert(Texture::State::Loaded == texture->GetState())
        this->_fontMap = texture;
    }

    inline float Text::GetSize() const
    {
        return this->_size;
    }

    inline void Text::SetSize(const float size)
    {
        _Assert(size > 0)
        this->_size = size;
    }

    inline Math::Vector4f Text::GetColor() const
    {
        return this->_color;
    }

    inline void Text::SetColor(const Math::Vector4f& color)
    {
        _Assert(color.a > 0.0f)
        this->_color = color;
    }
}

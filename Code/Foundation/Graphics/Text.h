// ----------------------------------------------------------------------------------------
//  \file       TexturedMesh.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Game/Attributes/HasPosition2D.h"
#include "Game/Attributes/HasRotation2D.h"
#include "Game/Attributes/HasScale.h"
#include "Graphics/Mesh.h"
#include "Graphics/Texture.h"
#include "Shaders/TextShader.h"

namespace Graphics
{
    class EXPORT Text : public Mesh, public HasPosition2D, public HasRotation2D, public HasScale
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
        
        float GetSpacing() const;
        void SetSpacing(float spacing);
        Math::Vector4f GetColor() const;
        void SetColor(const Math::Vector4f& color);

    private:
        std::shared_ptr<Texture> _fontMap;
        float _spacing;
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

    inline float Text::GetSpacing() const
    {
        return this->_spacing;
    }

    inline void Text::SetSpacing(const float spacing)
    {
        this->_spacing = spacing;
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

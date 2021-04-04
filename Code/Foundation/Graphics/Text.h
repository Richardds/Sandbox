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
        [[nodiscard]] std::shared_ptr<Texture> GetFontMap() const;
        void SetFontMap(const std::shared_ptr<Texture>& texture);

    private:
        std::shared_ptr<Texture> _fontMap;
    };
    
    inline std::shared_ptr<Texture> Text::GetFontMap() const
    {
        return this->_fontMap;
    }

    inline void Text::SetFontMap(const std::shared_ptr<Texture>& texture)
    {
        _Assert(texture);
        _Assert(Texture::State::Loaded == texture->GetState());
        this->_fontMap = texture;
    }
}

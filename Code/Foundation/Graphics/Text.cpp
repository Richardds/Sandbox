// ----------------------------------------------------------------------------------------
//  \file       TexturedMesh.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Text.h"
#include "Math/MathUtils.h"

Graphics::Text::Text(const std::shared_ptr<VertexArray>& vertexArrayObject,
                     const std::shared_ptr<Buffer>& vertexBuffer,
                     const std::shared_ptr<Buffer>& elementsBuffer,
                     const uint32_t elementsCount,
                     const std::shared_ptr<Texture>& fontMap) :
    Mesh(vertexArrayObject, vertexBuffer, elementsBuffer, elementsCount),
    _fontMap(fontMap),
    _size(24.0f),
    _color(1.0f)
{
}

Graphics::Text::Text(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Texture>& fontMap) :
    Text(mesh->GetVertexArray(), mesh->GetVertexBuffer(), mesh->GetElementBuffer(), mesh->GetElementsCount(), fontMap)
{
}

void Graphics::Text::Render(const std::shared_ptr<TextShader>& shader) const
{
    this->_fontMap->Activate(Texture::Bank::Font);

    shader->LoadTransformation(
        Math::TransformationMatrix2D(
            Math::Vector2f(0.0f, 0.0f),
            0.0f,
            1.0f
        )
    );
    shader->LoadColor(this->_color);

    this->DrawElements();
}

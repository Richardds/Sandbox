// ----------------------------------------------------------------------------------------
//  \file       TexturedMesh.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Graphics/Text.h"
#include "Math/MathUtils.h"

Graphics::Text::Text(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Texture>& fontMap) :
    _textMesh(mesh),
    _fontMap(fontMap),
    _spacing(1.0f),
    _color(1.0f)
{
}

void Graphics::Text::Render(const std::shared_ptr<TextShader>& shader) const
{
    this->_fontMap->Activate(Texture::Bank::Font);

    shader->LoadTransformation(
        Math::TransformationMatrix2D(
            this->_position,
            this->_rotation,
            this->_scale
        )
    );
    shader->LoadColor(this->_color);
    shader->LoadSmoothnessModifier(1.0f / this->_scale);

    this->_textMesh->DrawElements();
}

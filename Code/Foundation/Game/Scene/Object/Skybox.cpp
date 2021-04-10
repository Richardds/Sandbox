// ----------------------------------------------------------------------------------------
//  \file       Skybox.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Scene/Object/Skybox.h"
#include "Util/Generators/SkyboxGenerator.h"

Graphics::Skybox::Skybox(const std::shared_ptr<Texture>& texture, const float size) :
    _texture(texture),
    _size(size)
{
    _Assert(GL_TEXTURE_CUBE_MAP == texture->GetTarget())
    this->_mesh = Util::SkyboxGenerator::Instance().Generate(size);
}

void Graphics::Skybox::Render() const
{
    this->_texture->Activate(Texture::Bank::Skybox);

    this->_mesh->DrawElements();
}

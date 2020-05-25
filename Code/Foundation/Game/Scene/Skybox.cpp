// ----------------------------------------------------------------------------------------
//  \file       Skybox.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Scene/Skybox.h"
#include "Util/Generators/SkyboxGenerator.h"

Graphics::Skybox::Skybox(const std::shared_ptr<Texture>& texture) :
    Skybox(texture, DEFAULT_SKYBOX_SIZE)
{
}

Graphics::Skybox::Skybox(const std::shared_ptr<Texture>& texture, const float size) :
    _texture(texture),
    _size(size)
{
    this->_mesh = Util::SkyboxGenerator::Instance().Generate(size);
}

void Graphics::Skybox::Render() const
{
    this->_texture->Activate(Texture::Bank::Skybox);

    this->_mesh->DrawElements();
}

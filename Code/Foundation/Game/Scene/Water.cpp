// ----------------------------------------------------------------------------------------
//  \file       Water.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Scene/Water.h"
#include "Math/Utils.h"

Graphics::Water::Water() :
    _distortionOffset(0.0f),
    _distortionSpeed(DEFAULT_DISTORTION_SPEED),
    _tiling(DEFAULT_TILING)
{
}

void Graphics::Water::Update(const float delta)
{
    this->_distortionOffset += this->_distortionSpeed * delta;
    this->_distortionOffset = glm::mod(this->_distortionOffset, 1.0f);
}

void Graphics::Water::Render(const std::shared_ptr<WaterShader>& shader) const
{
    if (!this->_mesh)
    {
        return;
    }

    shader->LoadWorldTransformation(Math::TranslationMatrix(this->_position));
    shader->LoadDistortionOffset(this->_distortionOffset);
    shader->LoadTextureTiling(this->_tiling);

    const bool hasNormalMap = this->_mesh->HasNormalMap();
    shader->LoadHasNormalMap(hasNormalMap);
    if (hasNormalMap)
    {
        this->_mesh->GetNormalMap()->Activate(Texture::Bank::Normal);
    }

    const bool hasDistortionMap = this->_mesh->HasDistortionMap();
    shader->LoadHasDistortionMap(hasDistortionMap);
    if (hasDistortionMap)
    {
        this->_mesh->GetDistortionMap()->Activate(Texture::Bank::Distortion);
    }

    this->_mesh->DrawElements();
}

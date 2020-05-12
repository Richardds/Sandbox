#include "Water.h"
#include "../../Math/Utils.h"

Graphics::Water::Water() :
    _distortionOffset(0.0f),
    _distortionSpeed(DEFAULT_DISTORTION_SPEED)
{
}

Graphics::Water::~Water()
{
}

void Graphics::Water::Update(float delta)
{
    this->_distortionOffset += this->_distortionSpeed * delta;
    this->_distortionOffset = glm::mod(this->_distortionOffset, 1.0f);
}

void Graphics::Water::Render(std::shared_ptr<Graphics::WaterShader> shader)
{
    if (!this->_mesh) {
        return;
    }

    shader->LoadWorldTransformation(Math::TranslationMatrix(this->_position));
    shader->LoadDistortionOffset(this->_distortionOffset);

    bool hasDistortionMap = this->HasDistortionMap();
    shader->LoadHasDistortionMap(hasDistortionMap);
    if (hasDistortionMap) {
        this->_distortionMap->Activate(Texture::Bank::DISTORTION);
    }

    this->_mesh->DrawElements();
}

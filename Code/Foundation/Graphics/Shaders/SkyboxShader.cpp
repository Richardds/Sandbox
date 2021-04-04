// ----------------------------------------------------------------------------------------
//  \file       SkyboxShader.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Shaders/SkyboxShader.h"
#include "Core/Debug.h"
#include "Core/Types.h"
#include "Game/Scene/Camera.h"
#include "Graphics/Texture.h"
#include "Math/MathUtils.h"

Graphics::SkyboxShader::SkyboxShader() :
    ShaderSystem("Skybox"),
    _projectionLocation(-1),
    _viewLocation(-1),
    _textureLocation(-1),
    _darkeningFactorLocation(-1)
{
}

void Graphics::SkyboxShader::InitializeUniformVariables()
{
    // Setup transformations
    this->InitializeMatrix4fLocation("projection", Math::Matrix4f(1.0f), this->_projectionLocation);
    this->InitializeMatrix4fLocation("view", Math::Matrix4f(1.0f), this->_viewLocation);

    // Setup skybox texture
    this->InitializeIntLocation("skyboxSampler", EnumToValue(Texture::Bank::Skybox), this->_textureLocation);

    // Setup darkening factor
    this->InitializeFloatLocation("darkeningFactor", 1.0f, this->_darkeningFactorLocation);
}

void Graphics::SkyboxShader::LoadProjection(const std::shared_ptr<const Projection>& projection) const
{
    this->LoadMatrix4f(this->_projectionLocation, projection->GetMatrix());
}

void Graphics::SkyboxShader::LoadCamera(const std::shared_ptr<Camera>& camera) const
{
    _Assert(camera);

    Math::Matrix4f viewMatrix = Math::ViewMatrix(camera->GetPosition(), camera->GetRotationX(), camera->GetRotationY());
    viewMatrix[3].x = 0.0f;
    viewMatrix[3].y = 0.0f;
    viewMatrix[3].z = 0.0f;

    this->LoadMatrix4f(this->_viewLocation, viewMatrix);
}

void Graphics::SkyboxShader::LoadDarkeningFactor(const float darkeningFactor) const
{
    this->LoadFloat(this->_darkeningFactorLocation, darkeningFactor);
}

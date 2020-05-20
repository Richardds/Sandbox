#include "SkyboxShader.h"

#include "../Texture.h"
#include "../../Core/Debug.h"
#include "../../Game/Scene/Camera.h"
#include "../../Math/Utils.h"

Graphics::SkyboxShader::SkyboxShader() :
	ShaderSystem("Skybox"),
	_projectionLocation(-1),
	_viewLocation(-1),
	_textureLocation(-1)
{
}

void Graphics::SkyboxShader::InitializeUniformVariables()
{
	// Setup transformations
	this->InitializeMatrix4fLocation("projection", Math::Matrix4f(1.0f), this->_projectionLocation);
	this->InitializeMatrix4fLocation("view", Math::Matrix4f(1.0f), this->_viewLocation);

	// Setup skybox texture
	this->InitializeIntLocation("texture", EnumToValue(Texture::Bank::Diffuse), this->_textureLocation);
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

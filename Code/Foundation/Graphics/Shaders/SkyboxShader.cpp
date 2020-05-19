#include "SkyboxShader.h"
#include "../../Core/Debug.h"
#include "../../Game/Scene/Camera.h"
#include "../../Math/Utils.h"

Graphics::SkyboxShader::SkyboxShader() :
	ShaderSystem("Skybox"),
	_projectionLocation(-1),
	_viewLocation(-1)
{
}

void Graphics::SkyboxShader::InitializeUniformVariables()
{
	// Setup transformations
	this->InitializeMatrix4fLocation("projection", Math::Matrix4f(1.0f), this->_projectionLocation);
	this->InitializeMatrix4fLocation("view", Math::Matrix4f(1.0f), this->_viewLocation);
}

void Graphics::SkyboxShader::LoadProjection(const std::shared_ptr<const Projection>& projection) const
{
	this->LoadMatrix4f(this->_projectionLocation, projection->GetMatrix());
}

void Graphics::SkyboxShader::LoadCamera(const std::shared_ptr<Camera>& camera) const
{
	_Assert(camera);

	const Math::Matrix4f viewMatrix = Math::ViewMatrix(camera->GetPosition(), camera->GetRotationX(), camera->GetRotationY());
	this->LoadMatrix4f(this->_viewLocation, viewMatrix);
}

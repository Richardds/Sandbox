#include "SkyboxRenderer.h"
#include "../../IO/Console.h"
#include "../../Util/Generators/SkyboxGenerator.h"

Graphics::SkyboxRenderer::SkyboxRenderer() :
	_state(State::Initial)
{
}

bool Graphics::SkyboxRenderer::Setup(const std::shared_ptr<const Projection>& projection)
{
	_Assert(State::Initial == this->_state);

	// Setup skybox shader
	this->_shader = std::make_shared<SkyboxShader>();
	if (!this->_shader->Setup())
	{
		IO::Console::Instance().Error("Failed to load skybox shader\n");
		return false;
	}

	this->_shader->Use();
	this->_shader->LoadProjection(projection);

	this->_skyboxMesh = Util::SkyboxGenerator::Instance().Generate(250);

	this->_state = State::Ready;

	return true;
}

void Graphics::SkyboxRenderer::Begin(const std::shared_ptr<Camera>& camera) const
{
	this->_shader->Use();
	this->_shader->LoadCamera(camera);
}

void Graphics::SkyboxRenderer::Render(const std::shared_ptr<Skybox>& skybox) const
{
	_Assert(skybox);
	_Assert(State::Ready == this->_state);

	skybox->Render();
}

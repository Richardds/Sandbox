#include "EntityRenderer.h"
#include "../../IO/Console.h"

Graphics::EntityRenderer::EntityRenderer() :
	_state(State::Initial)
{
}

Graphics::EntityRenderer::~EntityRenderer()
{
}

bool Graphics::EntityRenderer::Setup(const std::shared_ptr<const Projection>& projection)
{
	_Assert(State::Initial == this->_state);

	// Setup entity shader
	this->_shader = std::make_shared<EntityShader>();
	if (!this->_shader->Setup())
	{
		IO::Console::Instance().Error("Failed to load entity shader\n");
		return false;
	}

	this->_shader->Use();
	this->_shader->LoadProjection(projection);

	this->_state = State::Ready;

	return true;
}

void Graphics::EntityRenderer::Begin(const std::shared_ptr<Camera>& camera,
                                     const std::shared_ptr<DirectionalLight>& sun,
                                     const std::unordered_map<std::string, std::shared_ptr<PointLight>>& lights) const
{
	this->_shader->Use();
	this->_shader->LoadCamera(camera);
	this->_shader->LoadSun(sun);
	this->_shader->LoadLights(lights);
}

void Graphics::EntityRenderer::Render(const std::shared_ptr<Entity>& entity) const
{
	_Assert(entity);
	_Assert(State::Ready == this->_state);

	entity->Render(this->_shader);
}

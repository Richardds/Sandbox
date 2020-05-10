#include "EntityRenderer.h"
#include "../../Math/Utils.h"
#include "../../IO/Console.h"

Graphics::EntityRenderer::EntityRenderer() :
	_state(State::INITIAL)
{
}

Graphics::EntityRenderer::~EntityRenderer()
{
}

bool Graphics::EntityRenderer::Setup(std::shared_ptr<const Projection> projection)
{
	_assert(State::INITIAL == this->_state);

	// Setup entity shader
	this->_shader = std::make_shared<EntityShader>();
	if (!this->_shader->Setup()) {
		IO::Console::Instance().Error("Failed to load entity shader\n");
		return false;
	}

	this->_shader->Use();
	this->_shader->LoadProjection(projection);

	this->_state = State::READY;

	return true;
}

void Graphics::EntityRenderer::Begin(std::shared_ptr<Camera> camera, std::shared_ptr<Sun> sun, const std::unordered_map<std::string, std::shared_ptr<Light>>& lights)
{
	this->_shader->Use();
	this->_shader->LoadCamera(camera);
	this->_shader->LoadSun(sun);
	this->_shader->LoadLights(lights);
}

void Graphics::EntityRenderer::Render(std::shared_ptr<Entity> entity)
{
	_assert(State::READY == this->_state);

	entity->Render(this->_shader);
}

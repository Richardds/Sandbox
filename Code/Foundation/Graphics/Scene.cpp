#include <iostream>

#include "Core.h"
#include "Scene.h"
#include "../Core/Debug.h"
#include "../IO/Mouse.h"
#include "../IO/Console.h"
#include "../Util/ResourcesLoader.h"

Graphics::Scene::Scene() :
    _state(State::INITIAL)
{
}

Graphics::Scene::~Scene()
{
}

Graphics::Scene::State Graphics::Scene::GetState() const
{
    return this->_state;
}

bool Graphics::Scene::Load()
{
    _assert(State::INITIAL == this->_state);

    // Setup entity shader
    this->_entityShader = std::make_shared<EntityShader>();
    if (!this->_entityShader->Load()) {
        IO::Console::Instance().Error("Failed to load entity shader\n");
        return false;
    }
    this->_entityShader->Use();

    // Setup projection
    std::shared_ptr<Window> context = Core::Instance().GetRenderingContext();
    this->_entityShader->LoadProjection(context->GetRatio(), 70.0f, 0.1f, 1000.0f);

    // Setup camera
    this->_camera = std::make_shared<Graphics::TargetedCamera>(15.0f);

    this->_state = State::RUN;

    return true;
}

void Graphics::Scene::ProcessInput()
{
    _assert(State::RUN == this->_state);
}

void Graphics::Scene::Update(float delta)
{
    _assert(State::RUN == this->_state);
}

void Graphics::Scene::Render()
{
    _assert(State::RUN == this->_state);

    this->_entityShader->Begin(this->_camera, this->_lights);

    for (auto& entity : this->_entities) {
        entity.second->Render(this->_entityShader);
    }
}

std::shared_ptr<Graphics::Light> Graphics::Scene::AddLight(const std::string& lightName)
{
    auto it = this->_lights.find(lightName);
    _assert(it == this->_lights.end());
    std::shared_ptr<Graphics::Light> light = std::make_shared<Graphics::Light>();
    this->_lights.emplace_hint(it, lightName, light);
    return light;
}

std::shared_ptr<Graphics::Entity> Graphics::Scene::AddEntity(const std::string& entityName, const std::string& resourceName)
{
    auto it = this->_entities.find(entityName);
    _assert(it == this->_entities.end());
    std::shared_ptr<Graphics::Entity> entity = std::make_shared<Graphics::Entity>();
    std::shared_ptr<Graphics::Model> model = Util::ResourcesLoader::Instance().LoadModel(resourceName);
    entity->SetModel(model);
    this->_entities.emplace_hint(it, entityName, entity);
    return entity;
}

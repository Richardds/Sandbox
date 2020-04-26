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

    // Setup shaders
    this->_entityShader = std::make_shared<EntityShader>();
    if (!this->_entityShader->Load()) {
        IO::Console::Instance().Error("Failed to load entity shader\n");
        return false;
    }

    // Setup projection
    std::shared_ptr<Window> context = Core::Instance().GetRenderingContext();
    this->_entityShader->SetProjection(context->GetRatio(), 70.0f, 0.1f, 1000.0f);

    this->_state = State::RUN;

    return true;
}

void Graphics::Scene::ProcessInput()
{
    _assert(State::RUN == this->_state);

    //if (IO::Mouse::Instance().IsKeyPressed(IO::Mouse::Key::LEFT)) {
    //    Math::Vector3f worldPosition = this->_entityShader->GetScreenWorldPosition(IO::Mouse::Instance().GetCoords());
    //    IO::Console::Instance().Info(" -> %f %f %f <-\n", worldPosition.x, worldPosition.y, worldPosition.z);
    //}
}

void Graphics::Scene::Update(Timing::Duration delta)
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
    std::shared_ptr<Graphics::Light> light = std::make_shared<Graphics::Light>();
    this->_lights[lightName] = light;
    return light;
}

std::shared_ptr<Graphics::Entity> Graphics::Scene::AddEntity(const std::string& entityName, const std::string& resourceName)
{
    std::shared_ptr<Graphics::Entity> entity = std::make_shared<Graphics::Entity>();
    std::shared_ptr<Graphics::Model> model = Util::ResourcesLoader::Instance().LoadModel(resourceName);
    entity->SetModel(model);
    this->_entities[entityName] = entity;
    return entity;
}

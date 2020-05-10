#include <iostream>

#include "Scene.h"
#include "../Graphics/Core.h"
#include "../Graphics/Projection.h"
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

bool Graphics::Scene::Setup()
{
    _assert(State::INITIAL == this->_state);

    // Setup camera
    this->_camera = std::make_shared<Graphics::TargetedCamera>(15.0f);

    // Setup global projection
    std::shared_ptr<Projection> projection = Core::Instance().MakeProjection(this->_camera->GetFieldOfView());

    // Setup entity renderer
    this->_entityRenderer = std::make_shared<EntityRenderer>();
    if (!this->_entityRenderer->Setup(projection)) {
        IO::Console::Instance().Error("Failed setup entity renderer\n");
        return false;
    }

    // Setup water renderer
    this->_waterRenderer = std::make_shared<WaterRenderer>();
    if (!this->_waterRenderer->Setup(projection)) {
        IO::Console::Instance().Error("Failed setup water renderer\n");
        return false;
    }

    // Setup sun
    this->_sun = std::make_shared<Sun>();
    this->_sun->SetDirection(Math::Vector3f(-1.0f, -1.0f, 0.0f));
    this->_sun->SetInstensity(0.15f);

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

    this->_waterRenderer->Begin(this->_camera, this->_sun);
    for (auto& water : this->_waterTiles) {
        this->_waterRenderer->Render(water.second);
    }

    this->_entityRenderer->Begin(this->_camera, this->_sun, this->_lights);
    for (auto& entity : this->_entities) {
        this->_entityRenderer->Render(entity.second);
    }
}

std::shared_ptr<Graphics::Water> Graphics::Scene::AddWater(const std::string& name, float size)
{
    auto it = this->_waterTiles.find(name);
    _assert(it == this->_waterTiles.end());
    std::shared_ptr<Model> waterModel = Util::ResourcesLoader::Instance().LoadModel("water");
    std::shared_ptr<Water> water = std::make_shared<Water>(waterModel->GetMesh("default"));
    this->_waterTiles.emplace_hint(it, name, water);
    return water;
}

std::shared_ptr<Graphics::Light> Graphics::Scene::AddLight(const std::string& name)
{
    auto it = this->_lights.find(name);
    _assert(it == this->_lights.end());
    std::shared_ptr<Light> light = std::make_shared<Light>();
    this->_lights.emplace_hint(it, name, light);
    return light;
}

std::shared_ptr<Graphics::Entity> Graphics::Scene::AddEntity(const std::string& name, const std::string& resourceName)
{
    auto it = this->_entities.find(name);
    _assert(it == this->_entities.end());
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    std::shared_ptr<Model> model = Util::ResourcesLoader::Instance().LoadModel(resourceName);
    entity->SetModel(model);
    this->_entities.emplace_hint(it, name, entity);
    return entity;
}

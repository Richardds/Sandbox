#include "Scene.h"
#include "../Core/Debug.h"
#include "../Graphics/Core.h"
#include "../Graphics/Projection.h"
#include "../Math/Utils.h"
#include "../IO/Console.h"
#include "../IO/Keyboard.h"
#include "../IO/Mouse.h"
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
    this->_camera->setRotationX(40.0f);

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

    // Setup HUD renderer
    this->_hudRenderer = std::make_shared<HUDRenderer>();
    if (!this->_hudRenderer->Setup(projection)) {
        IO::Console::Instance().Error("Failed setup HUD renderer\n");
        return false;
    }

    // Setup sun
    this->_sun = std::make_shared<DirectionalLight>();
    this->_sun->SetDirection(Math::Vector3f(0.0f, -1.0f, 1.0f));
    this->_sun->SetInstensity(0.6f);

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

    for (auto& water : this->_waterTiles) {
        water.second->Update(delta);
    }
}

void Graphics::Scene::Render()
{
    _assert(State::RUN == this->_state);

    this->RenderScene();
    
    this->_hudRenderer->RenderToMapBuffer([this]() {
        this->RenderScene();
    });

    this->_hudRenderer->Begin(Math::Vector3f(0.0f, 0.0f, 0.0f), 10.0f);
    this->_hudRenderer->Render(Math::Vector2f(-0.8f, -0.8f));
}

void Graphics::Scene::RenderScene()
{
    // Render the entities to the screen buffer
    this->_entityRenderer->Begin(this->_camera, this->_sun, this->_lights);
    this->RenderEntities();

    // Render the water tiles using multipass technique
    for (auto& water : this->_waterTiles) {
        // Render scene to water reflection frame buffer
        float distance = 2.0f * (this->_camera->getPositionY() - water.second->getPositionY());
        this->_camera->increasePositionY(-distance);
        this->_camera->invertRotationX();
        this->_entityRenderer->Begin(this->_camera, this->_sun, this->_lights);
        this->_entityRenderer->GetShader()->EnableClippingPlane(Math::Vector4f(0.0f, 1.0f, 0.0f, -water.second->getPositionY()));
        this->_waterRenderer->RenderToReflectionBuffer([this]() {
            this->RenderEntities();
        });
        this->_camera->increasePositionY(distance);
        this->_camera->invertRotationX();
        // Render scene to water refraction frame buffer
        this->_entityRenderer->Begin(this->_camera, this->_sun, this->_lights);
        this->_entityRenderer->GetShader()->EnableClippingPlane(Math::Vector4f(0.0f, -1.0f, 0.0f, water.second->getPositionY()));
        this->_waterRenderer->RenderToRefractionBuffer([this]() {
            this->RenderEntities();
        });
        this->_entityRenderer->GetShader()->DisableClippingPlane();
        // Now render to screen buffer
        this->_waterRenderer->Begin(this->_camera, this->_sun);
        this->_waterRenderer->Render(water.second);
    }
}

void Graphics::Scene::RenderEntities()
{
    for (auto& entity : this->_entities) {
        this->_entityRenderer->Render(entity.second);
    }
}

Math::Vector3f Graphics::Scene::GetScreenWorldPosition(Math::Vector2ui screenPosition) const
{
    Math::Vector4ui viewport = Graphics::Core::Instance().GetViewport();

    GLfloat depth;
    glReadPixels(screenPosition.x, viewport.w - screenPosition.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

    if (depth == 1.0f) {
        return Math::Vector3f(0.0f, 0.0f, 0.0f);
    }

    Math::Vector3f worldPosition = glm::unProject(
        Math::Vector3f(screenPosition.x, viewport.w - screenPosition.y, depth),
        Math::ViewMatrix(this->_camera->getPosition(), this->_camera->getRotationX(), this->_camera->getRotationY()),
        Core::Instance().MakeProjection(this->_camera->GetFieldOfView())->GetMatrix(),
        viewport
    );

    return worldPosition;
}

std::shared_ptr<Graphics::Water> Graphics::Scene::AddWater(const std::string& name, float size)
{
    auto it = this->_waterTiles.find(name);
    _assert(it == this->_waterTiles.end());
    std::shared_ptr<Model> waterModel = Util::ResourcesLoader::Instance().LoadModel("water");
    std::shared_ptr<Water> water = std::make_shared<Water>();
    std::shared_ptr<TexturedMesh> waterMesh = waterModel->GetMesh("_default");
    waterMesh->SetDistortionMap(Util::ResourcesLoader::Instance().LoadTexture("water_d"));
    water->SetMesh(waterMesh);
    this->_waterTiles.emplace_hint(it, name, water);
    return water;
}

std::shared_ptr<Graphics::PointLight> Graphics::Scene::AddLight(const std::string& name)
{
    auto it = this->_lights.find(name);
    _assert(it == this->_lights.end());
    std::shared_ptr<PointLight> light = std::make_shared<PointLight>();
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

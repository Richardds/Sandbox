// ----------------------------------------------------------------------------------------
//  \file       Scene.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Scene.h"
#include "Core/Debug.h"
#include "Graphics/Core.h"
#include "Graphics/Projection.h"
#include "IO/Console.h"
#include "IO/Keyboard.h"
#include "IO/Mouse.h"
#include "Math/MathUtils.h"
#include "Math/Physics/RigidBody/Plane.h"
#include "Util/ResourcesLoader.h"
#include "Util/Generators/PrimitiveGenerator.h"

Graphics::Scene::Scene() :
    _cursorPosition(0.0f, 0.0f, 0.0f),
    _time(0.0f),
    _renderSkybox(true),
    _paused(false),
    _state(State::Initial)
{
}

bool Graphics::Scene::Setup()
{
    _Assert(State::Initial == this->_state)

    // Setup camera
    this->_camera = std::make_shared<TargetedCamera>();

    // Setup global projection
    this->_projection = Core::Instance().CreateProjection(this->_camera->GetFieldOfView());

    // Setup entity renderer
    this->_skyboxRenderer = std::make_shared<SkyboxRenderer>();
    if (!this->_skyboxRenderer->Setup(this->_projection))
    {
        IO::Console::Instance().Error("Failed setup skybox renderer\n");
        return false;
    }

    // Setup entity renderer
    this->_entityRenderer = std::make_shared<EntityRenderer>();
    if (!this->_entityRenderer->Setup(this->_projection))
    {
        IO::Console::Instance().Error("Failed setup entity renderer\n");
        return false;
    }

    // Setup water renderer
    this->_waterRenderer = std::make_shared<WaterRenderer>();
    if (!this->_waterRenderer->Setup(this->_projection))
    {
        IO::Console::Instance().Error("Failed setup water renderer\n");
        return false;
    }

    // Setup text renderer
    this->_textRenderer = std::make_shared<TextRenderer>();
    if (!this->_textRenderer->Setup())
    {
        IO::Console::Instance().Error("Failed setup text renderer\n");
        return false;
    }

    // Setup sun
    this->_sun = std::make_shared<DirectionalLight>();
    this->_sun->SetColor(Math::Vector3f(1.0f, 0.95f, 0.85f));
    this->_sun->SetDirection(Math::Vector3f(-1.0f, 1.0f, -1.0f));
    this->_sun->SetIntensity(0.6f);

    // Setup flashlight
    this->_flashLight = std::make_shared<SpotLight>();

    // Setup text factory
    const std::shared_ptr<Font> font = Util::ResourcesLoader::Instance().LoadFont("tahoma");
    this->_textFactory = std::make_shared<Util::TextMeshGenerator>(font, 1.1f);

    // Setup physics engine
    this->_physics = std::make_shared<Math::PhysicsEngine>();
    this->_physics->Setup();

    // Add world plane
    const std::shared_ptr<Math::Plane> worldPlane = std::make_shared<Math::Plane>();
    this->_physics->Register(worldPlane);

    this->_state = State::Run;

    return true;
}

void Graphics::Scene::Reset()
{
    this->_skybox.reset();
    this->_entitiesMapping.clear();
    this->_entities.clear();
    this->_lightsMapping.clear();
    this->_lights.clear();
}

void Graphics::Scene::ProcessInput()
{
    _Assert(State::Run == this->_state)

    this->_cursorPosition = this->GetScreenWorldPosition(IO::Mouse::Instance().GetCoords());

    // Pause scene
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::P))
    {
        this->_paused = true;
    }

    // Resume scene
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::R))
    {
        this->_paused = false;
    }
}

void Graphics::Scene::Update(const float delta)
{
    _Assert(State::Run == this->_state)

    if (!this->_paused)
    {
        this->_time += delta;

        // Update physics engine
        this->_physics->Update(delta);

        // GoForward water distortion offset motion
        for (auto& [name, waterTile] : this->_waterTiles)
        {
            waterTile->Update(delta);
        }
    }
}

void Graphics::Scene::Render()
{
    _Assert(State::Run == this->_state)

    // Render the entities to the screen buffer
    this->RenderEntities();

    // Render the water tiles using multi-pass technique
    for (auto& [name, waterTile] : this->_waterTiles)
    {
        // Render scene to water reflection frame buffer
        // Cull everything under the water
        this->_entityRenderer->GetShader()->EnableClippingPlane(
            Math::Vector4f(0.0f, 1.0f, 0.0f, -waterTile->GetPositionY()));
        const float distance = 2.0f * (this->_camera->GetPositionY() - waterTile->GetPositionY());
        this->_camera->IncreasePositionY(-distance);
        this->_camera->InvertRotationX();
        this->_waterRenderer->RenderToReflectionBuffer([this]()
        {
            this->RenderSkybox();
            this->RenderEntities();
        });
        this->_camera->IncreasePositionY(distance);
        this->_camera->InvertRotationX();

        // Render scene to water refraction frame buffer
        // Cull everything 0.025 units above the water
        this->_entityRenderer->GetShader()->EnableClippingPlane(
            Math::Vector4f(0.0f, -1.0f, 0.0f, waterTile->GetPositionY() + 0.025f));
        this->_waterRenderer->RenderToRefractionBuffer([this]()
        {
            this->RenderSkybox();
            this->RenderEntities();
        });
        this->_entityRenderer->GetShader()->DisableClippingPlane();

        // Render the water tile to the screen buffer
        this->_waterRenderer->Begin(this->_camera, this->_sun, this->_lights, this->_flashLight);
        this->_waterRenderer->Render(waterTile);
    }

    // Render the skybox to the screen buffer
    this->RenderSkybox();

    // Render texts
    this->_textRenderer->Begin();
    glDisable(GL_DEPTH_TEST);
    for (const auto& [name, text] : this->_texts)
    {
        this->_textRenderer->Render(text);
    }
    glEnable(GL_DEPTH_TEST);
}


void Graphics::Scene::SetupSkybox(const std::string& name, const float size)
{
    std::shared_ptr<Texture> skyboxTexture = Util::ResourcesLoader::Instance().LoadTexture("Skybox/" + name, GL_TEXTURE_CUBE_MAP);
    this->_skybox = std::make_shared<Skybox>(skyboxTexture, size);
}

std::shared_ptr<Graphics::Text> Graphics::Scene::AddText(const std::string& name, const std::string& text)
{
    const auto it = this->_texts.find(name);
    _Assert(it == this->_texts.end())
    std::shared_ptr<Text> textMesh = this->_textFactory->Generate(text);

    this->_texts.emplace_hint(it, name, textMesh);

    return textMesh;
}

std::shared_ptr<Graphics::Water> Graphics::Scene::AddWater(const std::string& name, const float size)
{
    const auto it = this->_waterTiles.find(name);
    _Assert(it == this->_waterTiles.end())
    std::shared_ptr<TexturedMesh> waterMesh = std::make_shared<TexturedMesh>(
        Util::PrimitiveGenerator::Instance().Generate3dQuad(size)
    );
    waterMesh->SetDistortionMap(Util::ResourcesLoader::Instance().LoadTexture("water_d"));
    waterMesh->SetNormalMap(Util::ResourcesLoader::Instance().LoadTexture("water_n"));

    std::shared_ptr<Water> water = std::make_shared<Water>();
    water->SetMesh(waterMesh);
    water->SetTiling(size / 5.0f);

    this->_waterTiles.emplace_hint(it, name, water);

    return water;
}

std::shared_ptr<Graphics::PointLight> Graphics::Scene::AddLight(const std::string& name)
{
    const auto it = this->_lightsMapping.find(name);
    _Assert(it == this->_lightsMapping.end())
    std::shared_ptr<PointLight> light = this->AddLight();
    this->_lightsMapping.emplace_hint(it, name, light);
    return light;
}

std::shared_ptr<Graphics::PointLight> Graphics::Scene::AddLight()
{
    std::shared_ptr<PointLight> light = std::make_shared<PointLight>();
    this->_lights.emplace_back(light);
    return light;
}

std::shared_ptr<Graphics::Entity> Graphics::Scene::AddEntity(const std::string& resourceName)
{
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    entity->SetModel(Util::ResourcesLoader::Instance().LoadModel(resourceName));
    this->AddEntity(entity);
    return entity;
}

void Graphics::Scene::AddEntity(const std::shared_ptr<Entity>& entity)
{
    this->_entities.emplace_back(entity);
}

std::shared_ptr<Graphics::Entity> Graphics::Scene::AddEntity(const std::string& name, const std::string& resourceName)
{
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    entity->SetModel(Util::ResourcesLoader::Instance().LoadModel(resourceName));
    this->AddEntity(name, entity);
    return entity;
}

void Graphics::Scene::AddEntity(const std::string& name, const std::shared_ptr<Entity>& entity)
{
    const auto it = this->_entitiesMapping.find(name);
    _Assert(it == this->_entitiesMapping.end())
    this->AddEntity(entity);
    this->_entitiesMapping.emplace_hint(it, name, entity);
}

void Graphics::Scene::RenderEntities()
{
    this->_entityRenderer->Begin(this->_camera, this->_sun, this->_skybox, this->_lights, this->_flashLight);

    for (const auto& entity : this->_entities)
    {
        this->_entityRenderer->Render(entity);
    }
}

void Graphics::Scene::RenderSkybox() const
{
    if (this->_skybox != nullptr && this->_renderSkybox)
    {
        this->_skyboxRenderer->Begin(this->_camera);
        this->_skyboxRenderer->Render(this->_skybox);
    }
}

Math::Vector3f Graphics::Scene::GetScreenWorldPosition(const Math::Vector2ui& screenPosition) const
{
    const Math::Vector4ui viewport = Core::Instance().GetViewport();

    GLfloat depth;
    glReadPixels(screenPosition.x, viewport.w - screenPosition.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

    if (depth == 1.0f)
    {
        return Math::Vector3f(0.0f, 0.0f, 0.0f);
    }

    const Math::Vector3f worldPosition = unProject(
        Math::Vector3f(screenPosition.x, viewport.w - screenPosition.y, depth),
        Math::ViewMatrix3D(this->_camera->GetPosition(), this->_camera->GetRotation()),
        Core::Instance().CreateProjection(this->_camera->GetFieldOfView())->GetMatrix(),
        viewport
    );

    return worldPosition;
}

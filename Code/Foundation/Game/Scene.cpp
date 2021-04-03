// ----------------------------------------------------------------------------------------
//  \file       Scene.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Scene.h"
#include "Core/Debug.h"
#include "Graphics/Core.h"
#include "Graphics/Projection.h"
#include "IO/Console.h"
#include "IO/Keyboard.h"
#include "IO/Mouse.h"
#include "Math/Utils.h"
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

Graphics::Scene::State Graphics::Scene::GetState() const
{
    return this->_state;
}

bool Graphics::Scene::Setup()
{
    _Assert(State::Initial == this->_state);

    // Setup camera
    this->_camera = std::make_shared<TargetedCamera>();

    // Setup global projection
    this->_projection = Core::Instance().MakeProjection(this->_camera->GetFieldOfView());

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

    // Setup glyph renderer
    this->_glyphRenderer = std::make_shared<GlyphRenderer>();
    if (!this->_glyphRenderer->Setup())
    {
        IO::Console::Instance().Error("Failed setup glyph renderer\n");
        return false;
    }

    // Setup sun
    this->_sun = std::make_shared<DirectionalLight>();
    this->_sun->SetColor(Math::Vector3f(1.0f, 0.95f, 0.85f));
    this->_sun->SetDirection(Math::Vector3f(-1.0f, 1.0f, -1.0f));
    this->_sun->SetIntensity(0.6f);

    this->_flashLight = std::make_shared<SpotLight>();

    this->_state = State::Run;

    return true;
}

void Graphics::Scene::ProcessInput()
{
    _Assert(State::Run == this->_state);

    this->_cursorPosition = this->GetScreenWorldPosition(IO::Mouse::Instance().GetCoords());

    if (IO::Mouse::Instance().IsKeyPressed(IO::Mouse::Key::Middle))
    {
        IO::Console::Instance().Info("Click: %ff, %ff, %ff\n",
            this->_cursorPosition.x, this->_cursorPosition.y, this->_cursorPosition.z);
        IO::Console::Instance().Info("Position: %ff, %ff, %ff\n",
            this->_camera->GetPositionX(), this->_camera->GetPositionY(), this->_camera->GetPositionZ());
        IO::Console::Instance().Info("View: %ff, %ff, %ff\n",
            this->_camera->GetRotationX(), this->_camera->GetRotationY(), this->_camera->GetRotationZ());
    }

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
    _Assert(State::Run == this->_state);

    // Check camera angle threshold
    if (this->_camera->GetRotationX() < 0.5f)
    {
        this->_camera->SetRotationX(0.5f);
    }
    if (this->_camera->GetRotationX() > 179.5f)
    {
        this->_camera->SetRotationX(179.5f);
    }

    if (!this->_paused)
    {
        this->_time += delta;

        // GoForward water distortion offset motion
        for (auto& water : this->_waterTiles)
        {
            water.second->Update(delta);
        }
    }
}

void Graphics::Scene::Render()
{
    _Assert(State::Run == this->_state);

    // Render the entities to the screen buffer
    this->RenderEntities();

    // Render the water tiles using multi-pass technique
    for (auto& water : this->_waterTiles)
    {
        // Render scene to water reflection frame buffer
        // Cull everything under the water
        this->_entityRenderer->GetShader()->EnableClippingPlane(
            Math::Vector4f(0.0f, 1.0f, 0.0f, -water.second->GetPositionY()));
        const float distance = 2.0f * (this->_camera->GetPositionY() - water.second->GetPositionY());
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
            Math::Vector4f(0.0f, -1.0f, 0.0f, water.second->GetPositionY() + 0.025f));
        this->_waterRenderer->RenderToRefractionBuffer([this]()
        {
            this->RenderSkybox();
            this->RenderEntities();
        });
        this->_entityRenderer->GetShader()->DisableClippingPlane();

        // Render the water tile to the screen buffer
        this->_waterRenderer->Begin(this->_camera, this->_sun, this->_lights, this->_flashLight);
        this->_waterRenderer->Render(water.second);
    }

    // Render the skybox to the screen buffer
    this->RenderSkybox();
}

void Graphics::Scene::RenderEntities()
{
    this->_entityRenderer->Begin(this->_camera, this->_sun, this->_skybox, this->_lights, this->_flashLight);

    for (auto& entity : this->_entities)
    {
        this->_entityRenderer->Render(entity.second);
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
        Math::ViewMatrix(this->_camera->GetPosition(), this->_camera->GetRotationX(), this->_camera->GetRotationY()),
        Core::Instance().MakeProjection(this->_camera->GetFieldOfView())->GetMatrix(),
        viewport
    );

    return worldPosition;
}

std::shared_ptr<Graphics::Water> Graphics::Scene::AddWater(const std::string& name, const float size)
{
    const auto it = this->_waterTiles.find(name);
    _Assert(it == this->_waterTiles.end());
    std::shared_ptr<Water> water = std::make_shared<Water>();
    std::shared_ptr<TexturedMesh> waterMesh = std::make_shared<TexturedMesh>(
        Util::PrimitiveGenerator::Instance().Generate3dQuad(size));
    waterMesh->SetDistortionMap(Util::ResourcesLoader::Instance().LoadTexture("water_d"));
    waterMesh->SetNormalMap(Util::ResourcesLoader::Instance().LoadTexture("water_n"));
    water->SetMesh(waterMesh);
    water->SetTiling(size / 5.0f);
    this->_waterTiles.emplace_hint(it, name, water);
    return water;
}

std::shared_ptr<Graphics::PointLight> Graphics::Scene::AddLight(const std::string& name)
{
    const auto it = this->_lights.find(name);
    _Assert(it == this->_lights.end());
    std::shared_ptr<PointLight> light = std::make_shared<PointLight>();
    this->_lights.emplace_hint(it, name, light);
    return light;
}

std::shared_ptr<Graphics::Entity> Graphics::Scene::AddEntity(const std::string& name, const std::string& resourceName)
{
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    entity->SetModel(Util::ResourcesLoader::Instance().LoadModel(resourceName));
    return this->AddEntity(name, entity);
}

std::shared_ptr<Graphics::Entity> Graphics::Scene::AddEntity(const std::string& name,
                                                             const std::shared_ptr<Entity>& entity)
{
    const auto it = this->_entities.find(name);
    _Assert(it == this->_entities.end());
    this->_entities.emplace_hint(it, name, entity);
    return entity;
}

#include <iostream>

#include "Scene.h"
#include "Core.h"
#include "VertexAttributeConfig.h"
#include "../Core/Debug.h"
#include "../Util/ResourcesLoader.h"
#include "../IO/Keyboard.h"
#include "../IO/Mouse.h"
#include "../IO/Console.h"
#include "../Core/Debug.h"

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

    this->_uiShader = std::make_shared<UIShader>();
    if (!this->_uiShader->Load()) {
        IO::Console::Instance().Error("Failed to load UI shader\n");
        return false;
    }

    // Setup projection
    std::shared_ptr<Window> context = Core::Instance().GetRenderingContext();
    this->_entityShader->SetProjection(context->GetRatio(), 70.0f, 0.1f, 1000.0f);

    // Setup light
    this->_lights.emplace_back(std::make_shared<Light>(Math::Vector3f(0.0f, 10.0f, 0.0f), Math::Vector3f(1.0f, 1.0f, 1.0f), Math::Vector3f(1.0f, 0.01f, 0.05f)));

    this->_lights.emplace_back(std::make_shared<Light>(Math::Vector3f(-5.0f, 3.0f, -5.0f), Math::Vector3f(0.8f, 0.0f, 0.0f), Math::Vector3f(1.0f, 0.01f, 0.05f)));
    this->_lights.emplace_back(std::make_shared<Light>(Math::Vector3f(5.0f, 3.0f, -5.0f), Math::Vector3f(0.0f, 0.8f, 0.0f), Math::Vector3f(1.0f, 0.01f, 0.05f)));
    this->_lights.emplace_back(std::make_shared<Light>(Math::Vector3f(0.0f, 3.0f, 5.0f), Math::Vector3f(0.0f, 0.0f, 0.8f), Math::Vector3f(1.0f, 0.01f, 0.05f)));

    // Setup camera
    this->_camera = std::make_shared<TargetedCamera>(15.0f);

    // Setup terrain
    std::shared_ptr<Model> terrainModel = Util::ResourcesLoader::Instance().LoadModel("terrain");
    std::shared_ptr<TexturedMesh> terrainMesh = terrainModel->GetMesh("defaultobject");
    terrainMesh->SetDiffuseMap(Util::ResourcesLoader::Instance().LoadTexture("sand_d"));
    terrainMesh->SetNormalMap(Util::ResourcesLoader::Instance().LoadTexture("sand_n"));
    //terrainMesh->SetSpecularMap(Util::ResourcesLoader::Instance().LoadTexture("sand_s"));
    this->_entities.emplace_back(std::make_shared<Entity>(terrainModel));

    // Load and setup player
    std::shared_ptr<Model> playerModel = Util::ResourcesLoader::Instance().LoadModel("arrow");
    playerModel->GetMesh("defaultobject")->SetDiffuseMap(Util::ResourcesLoader::Instance().LoadTexture("arrow"));
    this->_player = std::make_shared<Player>(playerModel, Math::Vector3f({ 0.0f, 1.0f, 0.0f }));
    this->_entities.push_back(this->_player);
    
    // Load scene models
    std::shared_ptr<Model> crateModel = Util::ResourcesLoader::Instance().LoadModel("crate");
    std::shared_ptr<TexturedMesh> crateMesh = crateModel->GetMesh("defaultobject");
    crateMesh->SetDiffuseMap(Util::ResourcesLoader::Instance().LoadTexture("crate_d"));
    crateMesh->SetNormalMap(Util::ResourcesLoader::Instance().LoadTexture("crate_n"));
    this->_entities.push_back(std::make_shared<Entity>(crateModel, Math::Vector3f({ -5.0f, 1.0f, -5.0f }), 0.0f, 0.0f, 0.0f, 1.0f));
    this->_entities.push_back(std::make_shared<Entity>(crateModel, Math::Vector3f({ 5.0f, 1.0f, -5.0f }), 0.0f, 0.0f, 0.0f, 1.0f));
    this->_entities.push_back(std::make_shared<Entity>(crateModel, Math::Vector3f({ -5.0f, 1.0f, 5.0f }), 0.0f, 0.0f, 0.0f, 1.0f));
    this->_entities.push_back(std::make_shared<Entity>(crateModel, Math::Vector3f({ 5.0f, 1.0f, 5.0f }), 0.0f, 0.0f, 0.0f, 1.0f));

    std::shared_ptr<Model> bridgeModel = Util::ResourcesLoader::Instance().LoadModel("bridge");
    std::shared_ptr<TexturedMesh> bridgeMesh = bridgeModel->GetMesh("defaultobject");
    bridgeMesh->SetDiffuseMap(Util::ResourcesLoader::Instance().LoadTexture("bridge_d"));
    bridgeMesh->SetNormalMap(Util::ResourcesLoader::Instance().LoadTexture("bridge_n"));
    bridgeMesh->SetNormalMap(Util::ResourcesLoader::Instance().LoadTexture("bridge_s"));
    this->_entities.emplace_back(std::make_shared<Entity>(bridgeModel, Math::Vector3f(0.0f, 0.0f, -10.0f)));

    // Mouse scrolling
    IO::Mouse::Instance().RegisterScrolling([this](float x, float y) {
        this->_camera->IncreaseDistance(y);
    });

    this->_state = State::RUN;

    return true;
}

void Graphics::Scene::ProcessInput()
{
    _assert(State::RUN == this->_state);

    if (IO::Keyboard::Instance().IsAltPressed()) {
        if (IO::Mouse::Instance().IsKeyPressed(IO::Mouse::Key::LEFT)) {
            Math::Vector2f mouseMotion = IO::Mouse::Instance().GetRelativeGlMotion();
            mouseMotion *= 10.0f;
            this->_player->increasePosition(Math::Vector3f(-mouseMotion.x, 0.0f, mouseMotion.y));
        }

        return;
    }

    if (IO::Mouse::Instance().IsKeyPressed(IO::Mouse::Key::LEFT)) {
        Math::Vector3f worldPosition = this->_entityShader->GetScreenWorldPosition(IO::Mouse::Instance().GetCoords());
        IO::Console::Instance().Info(" -> %f %f %f <-\n", worldPosition.x, worldPosition.y, worldPosition.z);
    }
}

void Graphics::Scene::Update(Timing::Duration delta)
{
    _assert(State::RUN == this->_state);

    this->_player->LookAt(this->_entities[0]);
    this->_camera->Update(this->_player);
}

void Graphics::Scene::Render()
{
    _assert(State::RUN == this->_state);

    this->_entityShader->Begin(this->_camera, this->_lights);
    for (auto& entity : this->_entities) {
        entity->Render(this->_entityShader);
    }

    //this->_uiShader->Begin();
    //this->_quad->Render();
}

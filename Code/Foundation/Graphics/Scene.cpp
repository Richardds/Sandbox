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

    // Preload textures
    std::shared_ptr<Texture> metalTexture = Util::ResourcesLoader::Instance().LoadTexture("metal");
    std::shared_ptr<Texture> chinchillenTexture = Util::ResourcesLoader::Instance().LoadTexture("chinchillen");
    std::shared_ptr<Texture> arrowTexture = Util::ResourcesLoader::Instance().LoadTexture("arrow");

    // Setup light
    this->_light = std::make_shared<Light>(Math::Vector3f(0.0f, 3.0f, 0.0f), Math::Vector3f(1.0f, 1.0f, 1.0f));

    // Setup camera
    this->_camera = std::make_shared<TargetedCamera>(15.0f);

    // Setup terrain
    std::shared_ptr<Model> terrainModel = Util::ResourcesLoader::Instance().LoadModel("terrain");
    std::shared_ptr<Mesh> terrainMesh = terrainModel->GetMesh("default");
    terrainMesh->SetDiffuseMap(Util::ResourcesLoader::Instance().LoadTexture("sand_d"));
    terrainMesh->SetNormalMap(Util::ResourcesLoader::Instance().LoadTexture("sand_n"));
    this->_entities.emplace_back(std::make_shared<Entity>(terrainModel));

    // Load and setup player
    std::shared_ptr<Model> playerModel = Util::ResourcesLoader::Instance().LoadModel("arrow");
    playerModel->GetMesh("default")->SetDiffuseMap(arrowTexture);
    this->_player = std::make_shared<Player>(playerModel, Math::Vector3f({ 0.0f, 1.0f, 0.0f }));
    this->_entities.push_back(this->_player);
    
    // Load scene models
    std::shared_ptr<Model> cubeModel = Util::ResourcesLoader::Instance().LoadModel("cube");
    cubeModel->GetMesh("default")->SetDiffuseMap(metalTexture);
    this->_entities.push_back(std::make_shared<Entity>(cubeModel, Math::Vector3f({ -5.0f, 1.0f, -5.0f }), 0.0f, 0.0f, 0.0f, 1.0f));
    this->_entities.push_back(std::make_shared<Entity>(cubeModel, Math::Vector3f({ 5.0f, 1.0f, -5.0f }), 0.0f, 0.0f, 0.0f, 1.0f));
    this->_entities.push_back(std::make_shared<Entity>(cubeModel, Math::Vector3f({ -5.0f, 1.0f, 5.0f }), 0.0f, 0.0f, 0.0f, 1.0f));
    this->_entities.push_back(std::make_shared<Entity>(cubeModel, Math::Vector3f({ 5.0f, 1.0f, 5.0f }), 0.0f, 0.0f, 0.0f, 1.0f));

    //
    // Texture debug
    //
    //std::shared_ptr<VertexArray> quadVao = std::make_shared<Graphics::VertexArray>();
    //quadVao->Bind();
    //
    //std::shared_ptr<Buffer> quadEbo = std::make_shared<Graphics::Buffer>(GL_ELEMENT_ARRAY_BUFFER);
    //quadEbo->Bind();
    //quadEbo->Data<unsigned int>({
    //    0, 3, 1,
    //    1, 3, 2
    //});
    //
    //std::shared_ptr<Buffer> quadVbo = std::make_shared<Graphics::Buffer>(GL_ARRAY_BUFFER);
    //quadVbo->Bind();
    //quadVbo->Data<GLfloat>({
    //    0.25f,  0.25f, 0.0f,      1.0f, 1.0f,
    //    0.25f, -0.25f, 0.0f,      1.0f, 0.0f,
    //    -0.25f, -0.25f, 0.0f,     0.0f, 0.0f,
    //    -0.25f,  0.25f, 0.0f,     0.0f, 1.0f
    //});
    //
    //VertexAttributeConfig attributes;
    //attributes.Append(GL_FLOAT, 3);
    //attributes.Append(GL_FLOAT, 2);
    //attributes.Apply(quadVao);
    //
    //quadVao->Unbind();
    //quadEbo->Unbind();
    //quadVbo->Unbind();
    //
    //this->_quad = std::make_shared<Model>();
    //std::shared_ptr<Mesh> quadMesh = std::make_shared<Mesh>(quadVao, quadVbo, quadEbo, 6);
    //quadMesh->SetTexture(chinchillenTexture);
    //this->_quad->AddMesh("default", quadMesh);
    //this->_quad->FinishLoading();

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

    // Camera movemement
    if (IO::Keyboard::Instance().IsAltPressed()) {
        if (IO::Mouse::Instance().IsKeyPressed(IO::Mouse::Key::LEFT)) {
            Math::Vector2f mouseMotion = IO::Mouse::Instance().GetRelativeGlMotion();
            mouseMotion *= 10.0f;
            this->_player->increasePosition(Math::Vector3f(-mouseMotion.x, 0.0f, mouseMotion.y));
        }

        return;
    }

    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::UP)) {
        this->_player->increasePosition(0.0f, 0.0f, -0.25f);
    }

    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::DOWN)) {
        this->_player->increasePosition(0.0f, 0.0f, 0.25f);
    }

    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::LEFT)) {
        this->_player->increasePosition(-0.25f, 0.0f, 0.0f);
    }

    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::RIGHT)) {
        this->_player->increasePosition(0.25f, 0.0f, 0.0f);
    }

    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::P)) {
        this->_player->increasePosition(0.0f, 0.25f, 0.0f);
    }

    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::L)) {
        this->_player->increasePosition(0.0f, -0.25f, 0.0f);
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

    this->_entityShader->Begin(this->_camera, this->_light);
    for (auto& entity : this->_entities) {
        entity->Render(this->_entityShader);
    }

    //this->_uiShader->Begin();
    //this->_quad->Render();
}

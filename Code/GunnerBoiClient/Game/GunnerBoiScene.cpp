#include <Game/Light.h>
#include <Game/TargetedCamera.h>
#include <Graphics/Model.h>
#include <Graphics/TexturedMesh.h>
#include <Game/Entity.h>
#include <Util/ResourcesLoader.h>
#include <IO/Mouse.h>
#include <IO/Keyboard.h>
#include <IO/Console.h>

#include "GunnerBoiScene.h"

GunnerBoi::GunnerBoiScene::GunnerBoiScene()
{
}

GunnerBoi::GunnerBoiScene::~GunnerBoiScene()
{
}

bool GunnerBoi::GunnerBoiScene::Load()
{
    _assert(Graphics::Scene::Load());

    // Create projectile manager
    this->_projectileManager = std::make_shared<ProjectileManager>();

    // Configure camera
    this->_camera->SetDistance(10.0f);

    // Configure sun
    this->_entityShader->LoadSun(0.15f, Math::Vector3f(0.85f, 0.65f, 0.75f));

    // Configure lights
    std::shared_ptr<Graphics::Light> pointLight = this->AddLight("point_light");
    pointLight->setPosition(Math::Vector3f(0.0f, 10.0f, 0.0f));
    pointLight->SetAttenuation(Math::Vector3f(1.0f, 0.045f, 0.0075f));

    // Load terrain
    std::shared_ptr<Graphics::Entity> terrain = this->AddEntity("terrain", "terrain");

    // Load player
    this->_player = this->SetupPlayer("arrow", Math::Vector3f(0.0f, 0.0f, 0.0f));

    // Load other models
    std::shared_ptr<Graphics::Entity> crate1 = this->AddEntity("crate_01", "crate");
    crate1->setPosition(Math::Vector3f(-5.0f, 0.0f, -5.0f));
    std::shared_ptr<Graphics::Entity> crate2 = this->AddEntity("crate_02", "crate");
    crate2->setPosition(Math::Vector3f(5.0f, 0.0f, -5.0f));
    std::shared_ptr<Graphics::Entity> crate3 = this->AddEntity("crate_03", "crate");
    crate3->setPosition(Math::Vector3f(-5.0f, 0.0f, 5.0f));
    std::shared_ptr<Graphics::Entity> crate4 = this->AddEntity("crate_04", "crate");
    crate4->setPosition(Math::Vector3f(5.0f, 0.0f, 5.0f));

    std::shared_ptr<Graphics::Entity> rock = this->AddEntity("rock_01", "rock");
    rock->setPosition(Math::Vector3f(3.0f, 0.0f, 3.0f));

    // Mouse scrolling
    IO::Mouse::Instance().RegisterScrolling([this](float x, float y) {
        this->_camera->IncreaseDistance(y);
    });

    return true;
}

void GunnerBoi::GunnerBoiScene::ProcessInput()
{
    Graphics::Scene::ProcessInput();

    if (IO::Mouse::Instance().IsKeyPressed(IO::Mouse::Key::LEFT)) {
        Math::Vector3f worldPosition = this->_entityShader->GetScreenWorldPosition(IO::Mouse::Instance().GetCoords());
        Math::Vector2f target = Math::Vector2f(worldPosition.x, worldPosition.z);
        if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::LEFT_SHIFT)) {
            this->_player->Idle();
            this->_player->LookAt(target);
            
            if (this->_player->IsReadyToFire()) {
                this->_projectileManager->Manage(this->_player->Fire());
            }
        }
        else {
            this->_player->SetTarget(target);
            this->_player->Follow();
        }
    }

    //if (IO::Mouse::Instance().IsKeyPressed(IO::Mouse::Key::LEFT)) {
    //    Math::Vector2f mouseMotion = IO::Mouse::Instance().GetRelativeGlMotion();
    //    mouseMotion *= 10.0f;
    //    this->_player->increasePosition(Math::Vector3f(-mouseMotion.x, 0.0f, mouseMotion.y));
    //}
}

void GunnerBoi::GunnerBoiScene::Update(float delta)
{
    Graphics::Scene::Update(delta);

    this->_projectileManager->Update(delta);

    this->_player->Update(delta);
    this->_camera->Update(this->_player);

    Math::Vector3f playerPosition = this->_player->getPosition();
    float lightPositionY = this->_lights["point_light"]->getPositionY();
    this->_lights["point_light"]->setPosition(Math::Vector3f(playerPosition.x, lightPositionY, playerPosition.z));
}

void GunnerBoi::GunnerBoiScene::Render()
{
    Graphics::Scene::Render();

    this->_projectileManager->Render(this->_entityShader);
    this->_player->Render(this->_entityShader);
}

std::shared_ptr<GunnerBoi::Boi> GunnerBoi::GunnerBoiScene::SetupPlayer(const std::string& resourceName, Math::Vector3f position)
{
    std::shared_ptr<Boi> player = std::make_shared<Boi>(position);
    std::shared_ptr<Graphics::Model> model = Util::ResourcesLoader::Instance().LoadModel(resourceName);
    player->SetModel(model);
    return player;
}

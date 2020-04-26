#include <Graphics/Scene/Light.h>
#include <Graphics/Scene/TargetedCamera.h>
#include <Graphics/Model.h>
#include <Graphics/TexturedMesh.h>
#include <Graphics/Scene/Entity.h>
#include <Util/ResourcesLoader.h>
#include <IO/Mouse.h>
#include <IO/Keyboard.h>

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

    // Setup camera
    this->_camera = std::make_shared<Graphics::TargetedCamera>(10.0f);

    // Setup light
    std::shared_ptr<Graphics::Light> pointLight = this->AddLight("point_light");
    pointLight->setPosition(Math::Vector3f(0.0f, 10.0f, 0.0f));
    pointLight->SetAttenuation(Math::Vector3f(this->_lightA, this->_lightB, this->_lightC));

    // Setup terrain
    std::shared_ptr<Graphics::Entity> terrain = this->AddEntity("terrain", "terrain");

    // Load player
    this->_player = this->SetupPlayer("sphere");

    // Load scene models
    std::shared_ptr<Graphics::Entity> crate1 = this->AddEntity("crate_01", "crate");
    crate1->setPosition(Math::Vector3f(-5.0f, 0.0f, -5.0f));
    std::shared_ptr<Graphics::Entity> crate2 = this->AddEntity("crate_02", "crate");
    crate2->setPosition(Math::Vector3f(5.0f, 0.0f, -5.0f));
    std::shared_ptr<Graphics::Entity> crate3 = this->AddEntity("crate_03", "crate");
    crate3->setPosition(Math::Vector3f(-5.0f, 0.0f, 5.0f));
    std::shared_ptr<Graphics::Entity> crate4 = this->AddEntity("crate_04", "crate");
    crate4->setPosition(Math::Vector3f(5.0f, 0.0f, 5.0f));

    // Mouse scrolling
    IO::Mouse::Instance().RegisterScrolling([this](float x, float y) {
        this->_camera->IncreaseDistance(y);
    });

    return true;
}

void GunnerBoi::GunnerBoiScene::ProcessInput()
{
    Graphics::Scene::ProcessInput();

    if (IO::Keyboard::Instance().IsAltPressed()) {
        if (IO::Mouse::Instance().IsKeyPressed(IO::Mouse::Key::LEFT)) {
            Math::Vector2f mouseMotion = IO::Mouse::Instance().GetRelativeGlMotion();
            mouseMotion *= 10.0f;
            this->_player->increasePosition(Math::Vector3f(-mouseMotion.x, 0.0f, mouseMotion.y));
        }

        return;
    }
}

void GunnerBoi::GunnerBoiScene::Update(Timing::Duration delta)
{
    Graphics::Scene::Update(delta);

    this->_player->LookAt(this->_entities["terrain"]); // TODO: Getter
    this->_camera->Update(this->_player);
}

void GunnerBoi::GunnerBoiScene::Render()
{
    Graphics::Scene::Render();

    this->_player->Render(this->_entityShader);
}

std::shared_ptr<GunnerBoi::Boi> GunnerBoi::GunnerBoiScene::SetupPlayer(const std::string& resourceName)
{
    std::shared_ptr<Boi> player = std::make_shared<Boi>();
    std::shared_ptr<Graphics::Model> model = Util::ResourcesLoader::Instance().LoadModel(resourceName);
    player->SetModel(model);
    return player;
}

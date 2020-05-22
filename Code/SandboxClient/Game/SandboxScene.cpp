#include "Precompiled.h"

#include <IO/Keyboard.h>
#include <IO/Mouse.h>
#include <Util/ResourcesLoader.h>

#include "SandboxScene.h"

Sandbox::SandboxScene::SandboxScene() :
	_lockCameraToPlayer(true)
{
}

bool Sandbox::SandboxScene::Setup()
{
	_Assert(Graphics::Scene::Setup());

	// Create projectile manager
	this->_projectileManager = std::make_shared<ProjectileManager>();

	// Configure camera
	this->_camera->SetDistance(10.0f);

	// Load Skybox
	std::shared_ptr<Graphics::Texture> skyboxTexture = Util::ResourcesLoader::Instance().LoadCubeMap("day");
	this->_skybox = std::make_shared<Graphics::Skybox>(skyboxTexture, 500.0f);
	
	// Configure lights
	std::shared_ptr<Graphics::PointLight> playerLight = this->AddLight("player_light");
	playerLight->SetPosition(Math::Vector3f(0.0f, 5.0f, 0.0f));
	playerLight->SetAttenuation(Math::Vector3f(1.0f, 0.045f, 0.0095f));

	// Load terrain
	std::shared_ptr<Graphics::Entity> terrain = this->AddEntity("terrain", "terrain");

	// Load water
	std::shared_ptr<Graphics::Water> water = this->AddWater("default", 500.0f);

	// Load player
	this->_player = this->SetupPlayer("arrow");

	// Load other models	
	std::shared_ptr<Graphics::Entity> crate1 = this->AddEntity("crate_01", "crate");
	crate1->SetPosition(Math::Vector3f(-1.5f, 0.0f, -3.0f));
	std::shared_ptr<Graphics::Entity> crate2 = this->AddEntity("crate_02", "crate");
	crate2->SetPosition(Math::Vector3f(1.5f, 0.0f, -3.0f));
	std::shared_ptr<Graphics::Entity> crate3 = this->AddEntity("crate_03", "crate");
	crate3->SetPosition(Math::Vector3f(0.0f, 1.5f, -3.0f));
	crate3->SetRotationY(45.0f);
	std::shared_ptr<Graphics::Entity> crate4 = this->AddEntity("crate_04", "crate");
	crate4->SetPosition(Math::Vector3f(3.25f, 0.0f, -1.75f));
	std::shared_ptr<Graphics::Entity> rock1 = this->AddEntity("rock_01", "rock");
	rock1->SetPosition(Math::Vector3f(-3.25f, 0.0f, -1.65f));
	std::shared_ptr<Graphics::Entity> brickWall = this->AddEntity("brick_wall_01", "brick_wall");
	brickWall->SetPosition(Math::Vector3f(7.5f, 0.0f, -5.0f));
	brickWall->SetRotationY(-45.0f);

	// Register mouse scrolling
	IO::Mouse::Instance().RegisterScrolling([this](float x, float y)
	{
		if (this->_lockCameraToPlayer)
		{
			this->_camera->IncreaseDistance(y);
		}
	});

	return true;
}

void Sandbox::SandboxScene::ProcessInput()
{
	Scene::ProcessInput();

	const Math::Vector3f worldPosition = this->GetScreenWorldPosition(IO::Mouse::Instance().GetCoords());
	const Math::Vector2f worldPointer = Math::Vector2f(worldPosition.x, worldPosition.z);

	// Player navigation and interaction
	if (IO::Mouse::Instance().IsKeyPressed(IO::Mouse::Key::Left))
	{
		this->_player->LookAt(worldPointer);
		if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::LeftShift))
		{
			this->_player->Idle();

			if (this->_player->IsReadyToFire())
			{
				this->_player->SingleFire(this->_projectileManager);
			}
		}
		else
		{
			this->_player->SetTarget(worldPointer);
			this->_player->Follow();
		}
	}
	// Camera motion
	else if (IO::Mouse::Instance().IsKeyPressed(IO::Mouse::Key::Right))
	{
		Math::Vector2f mouseMotion = IO::Mouse::Instance().GetRelativeGlMotion();
		mouseMotion *= 75.0f;

		// Invert camera motion on free camera
		if (!this->_lockCameraToPlayer)
		{
			mouseMotion *= -1;
		}

		this->_camera->IncreaseRotation(-mouseMotion.y, mouseMotion.x, 0.0f);
	}

	// Additional skills
	if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::X))
	{
		if (this->_player->IsReadyToFire())
		{
			this->_player->StarFire(this->_projectileManager, 5);
		}
	}
	else if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::Z))
	{
		if (this->_player->IsReadyToFire())
		{
			this->_player->LookAt(worldPointer);
			this->_player->BeamFire(this->_projectileManager, 4);
		}
	}

	// Camera modes
	if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::One))
	{
		this->_lockCameraToPlayer = true;
	}
	else if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::Two))
	{
		this->_lockCameraToPlayer = false;
		this->_camera->SetPosition(Math::Vector3f(-10.0f, 10.0f, 5.0f));
		this->_camera->LookAt(Math::Vector3f(0.0f, 0.0f, 0.0f));
	}
	else if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::Three))
	{
		this->_lockCameraToPlayer = false;
		this->_camera->SetPosition(Math::Vector3f(15.0f, 20.0f, 10.0f));
		this->_camera->LookAt(Math::Vector3f(0.0f, 0.0f, 0.0f));
	}

	// Enabled fog
	if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::F))
	{
		this->_renderSkybox = false;
		this->_waterRenderer->GetShader()->Use();
		this->_waterRenderer->GetShader()->LoadFogEnabled(true);
		this->_entityRenderer->GetShader()->Use();
		this->_entityRenderer->GetShader()->LoadFogEnabled(true);
	}

	// Disable fog
	if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::G))
	{
		this->_renderSkybox = true;
		this->_waterRenderer->GetShader()->Use();
		this->_waterRenderer->GetShader()->LoadFogEnabled(false);
		this->_entityRenderer->GetShader()->Use();
		this->_entityRenderer->GetShader()->LoadFogEnabled(false);
	}
}

void Sandbox::SandboxScene::Update(const float delta)
{
	Scene::Update(delta);

	this->_projectileManager->Update(delta);

	this->_player->Update(delta);

	if (this->_lockCameraToPlayer)
	{
		this->_camera->Spectate(this->_player->GetPosition());
	}

	// Update player light position
	const Math::Vector3f playerPosition = this->_player->GetPosition();
	const float lightPositionY = this->_lights["player_light"]->GetPositionY();
	this->_lights["player_light"]->SetPosition(Math::Vector3f(playerPosition.x, lightPositionY, playerPosition.z));

	// Time based updates
	if (!this->_paused)
	{
		// GoForward water motion
		this->_waterTiles["default"]->SetPositionY(glm::sin(this->_time / 1.75f) / 35.0f);

		// GoForward scene day & night cycle effect
		const float darkeningFactor = (glm::sin(this->_time / 5.0f) + 1.0f) / (2.0f / (1.0f - SUN_LOWER_LIMIT)) + SUN_LOWER_LIMIT; // Interval <SUN_LOWER_LIMIT-1.000>
		this->_skyboxRenderer->GetShader()->Use();
		this->_skyboxRenderer->GetShader()->LoadDarkeningFactor(darkeningFactor);
		this->_sun->SetIntensity(darkeningFactor);
	}
}

void Sandbox::SandboxScene::Render()
{
	Scene::Render();
}

void Sandbox::SandboxScene::RenderEntities()
{
	Scene::RenderEntities();
	this->_projectileManager->RenderWith(this->_entityRenderer);
}

std::shared_ptr<Sandbox::Player> Sandbox::SandboxScene::SetupPlayer(const std::string& resourceName)
{
	const std::string playerEntityName = "player";
	const auto it = this->_entities.find(playerEntityName);
	_Assert(it == this->_entities.end());
	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->SetModel(Util::ResourcesLoader::Instance().LoadModel(resourceName));
	this->_entities.emplace_hint(it, playerEntityName, player);
	return player;
}

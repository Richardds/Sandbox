#pragma once

#include <vector>

#include <Game/Scene.h>
#include <Game/Scene/TargetedCamera.h>

#include "Scene/Boi.h"
#include "Managers/ProjectileManager.h"

namespace GunnerBoi
{

    class GunnerBoiScene : public Graphics::Scene
    {
    public:
        enum class State {
            INITIAL,
            RUN
        };

        GunnerBoiScene();
        virtual ~GunnerBoiScene();
        bool Setup();
        void ProcessInput();
        void Update(float delta);
        void Render();
        std::shared_ptr<Boi> SetupPlayer(const std::string& resourceName);

    protected:
        void RenderEntities();

    private:
        std::shared_ptr<Boi> _player;
        std::shared_ptr<ProjectileManager> _projectileManager;

        bool _lockCameraToPlayer;
    };

}

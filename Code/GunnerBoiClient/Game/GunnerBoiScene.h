#pragma once

#include <Graphics/Scene.h>
#include <Graphics/Scene/TargetedCamera.h>

#include "Scene/Boi.h"
#include "../Managers/ProjectileManager.h"

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
        bool Load();
        void ProcessInput();
        void Update(float delta);
        void Render();
        std::shared_ptr<Boi> SetupPlayer(const std::string& resourceName);

    private:
        std::shared_ptr<Boi> _player;
        std::shared_ptr<ProjectileManager> _projectileManager;
    };

}

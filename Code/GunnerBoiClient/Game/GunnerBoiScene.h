#pragma once

#include <Graphics/Scene.h>
#include <Timing/Time.h>
#include <Graphics/Scene/TargetedCamera.h>

#include "Scene/Boi.h"

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
        void Update(Timing::Duration delta);
        void Render();
        std::shared_ptr<Boi> SetupPlayer(const std::string& resourceName);

    private:
        std::shared_ptr<Graphics::Player> _player;
        float _lightA = 1.0f;
        float _lightB = 0.01f;
        float _lightC = 0.005f;
    };

}

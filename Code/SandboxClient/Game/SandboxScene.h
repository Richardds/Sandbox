// ----------------------------------------------------------------------------------------
//  \file       SandboxScene.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include <Game/Scene.h>

#include "App/RenderApplication.h"
#include "Managers/DuckManager.h"
#include "Managers/ProjectileManager.h"
#include "Scene/Player.h"

namespace Sandbox
{
    /// 3D scene overrider of base scene class
    class SandboxScene : public Graphics::Scene
    {
    public:
        enum class State
        {
            Initial,
            Run
        };

        static constexpr float SUN_LOWER_LIMIT = 0.15f;

        SandboxScene();

        bool Setup() override;
        void Reset() override;
        bool OnSceneSetup() override;
        void ProcessCameraInput();
        void ProcessPlayerInput();
        void ProcessFlashLight() const;
        void ProcessInput() override;
        void Update(float delta) override;
        void UpdateDebugInformation(const App::RenderApplication::Stats& stats) const;
        std::shared_ptr<Player> SetupPlayer(const std::string& resourceName);

    protected:
        void RenderEntities() const override;

    private:
        std::shared_ptr<Player> _player;
        std::shared_ptr<ProjectileManager> _projectileManager;
        std::shared_ptr<DuckManager> _duckManager;
        std::shared_ptr<Graphics::Text> _textStats;

        bool _lockCameraToPlayer;
    };
}

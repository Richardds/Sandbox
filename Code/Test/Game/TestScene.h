// ----------------------------------------------------------------------------------------
//  \file       TestScene.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include <Game/Scene.h>

namespace Sandbox
{
    /// 3D scene overrider of base scene class
    class TestScene : public Graphics::Scene
    {
    public:
        enum class State
        {
            Initial,
            Run
        };

        TestScene() = default;

        bool Setup() override;
        void ProcessCameraInput() const;
        void ProcessInput() override;
        void Update(float delta) override;
        void Render() override;
    };
}

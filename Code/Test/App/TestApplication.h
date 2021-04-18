// ----------------------------------------------------------------------------------------
//  \file       TestApplication.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include <App/RenderApplication.h>

#include "Game/TestScene.h"

namespace Sandbox
{
    /// Sandbox application overrider class
    class TestApplication : public App::RenderApplication
    {
    public:
        TestApplication() = default;

        bool Open() override;
        void Close() override;

    protected:
        void OnProcessInput() override;
        void OnUpdateLogic() override;
        void OnUpdateFrame() override;

    private:
        std::shared_ptr<TestScene> _scene;
    };
}

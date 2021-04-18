// ----------------------------------------------------------------------------------------
//  \file       SandboxApplication.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include <App/RenderApplication.h>

#include "Game/SandboxScene.h"

namespace Sandbox
{
    /// Sandbox application overrider class
    class SandboxApplication : public App::RenderApplication
    {
    public:
        SandboxApplication() = default;

        bool Open() override;
        void Close() override;

    protected:
        void OnProcessInput() override;
        void OnUpdateLogic() override;
        void OnUpdateFrame() override;
        void LoadScene(const std::string& name);

    private:
        std::shared_ptr<SandboxScene> _scene;
    };
}

// ----------------------------------------------------------------------------------------
//  \file       SandboxApplication.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include <Precompiled.h>
#include <IO/Keyboard.h>

#include "App/SandboxApplication.h"

bool Sandbox::SandboxApplication::Open()
{
    if (RenderApplication::Open())
    {
        this->PrintDeviceInfo();

        this->_scene = std::make_shared<SandboxScene>();
        _Assert(this->_scene->Setup())

        return true;
    }

    return false;
}

void Sandbox::SandboxApplication::Close()
{
    RenderApplication::Close();
}

void Sandbox::SandboxApplication::OnProcessInput()
{
    // Disable full screen
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::Escape))
    {
        Graphics::Core::Instance().GetRenderingContext()->ExitFullScreen();
    }

    // Enable full screen
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::F5))
    {
        Graphics::Core::Instance().GetRenderingContext()->EnterFullScreen();
    }

    // Disable wireframe mode
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::F8))
    {
        this->SetWireframeModeEnabled(false);
    }

    // Enable wireframe mode
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::F9))
    {
        this->SetWireframeModeEnabled(true);
    }

    // Disable vertical sync
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::F10))
    {
        this->SetVSyncEnabled(false);
    }

    // Enable vertical sync
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::F11))
    {
        this->SetVSyncEnabled(true);
    }

    this->_scene->ProcessInput();
}

void Sandbox::SandboxApplication::OnUpdateLogic()
{
    this->_scene->Update(this->GetFrameDelta());
}

void Sandbox::SandboxApplication::OnUpdateFrame()
{
    this->_scene->Render();
}

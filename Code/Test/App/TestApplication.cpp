// ----------------------------------------------------------------------------------------
//  \file       TestApplication.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include <Precompiled.h>
#include <IO/Keyboard.h>

#include "App/TestApplication.h"

bool Sandbox::TestApplication::Open()
{
    if (RenderApplication::Open())
    {
        this->PrintDeviceInfo();

        this->_scene = std::make_shared<TestScene>();
        _Assert(this->_scene->Setup())

        return true;
    }

    return false;
}

void Sandbox::TestApplication::Close()
{
    RenderApplication::Close();
}

void Sandbox::TestApplication::OnProcessInput()
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

void Sandbox::TestApplication::OnUpdateLogic()
{
    this->_scene->Update(this->GetFrameDelta());
}

void Sandbox::TestApplication::OnUpdateFrame()
{
    this->_scene->Render();
}

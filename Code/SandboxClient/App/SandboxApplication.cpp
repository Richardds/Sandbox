// ----------------------------------------------------------------------------------------
//  \file       SandboxApplication.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include <IO/Keyboard.h>
#include <Core/Exception.h>
#include <IO/Console.h>
#include <Util/ResourcesLoader.h>

#include "App/SandboxApplication.h"

Sandbox::SandboxApplication::SandboxApplication() :
    _sceneName("default")
{
}

bool Sandbox::SandboxApplication::Open()
{
    if (RenderApplication::Open())
    {
        this->PrintDeviceInfo();

        this->_scene = std::make_shared<SandboxScene>();
        _Assert(this->_scene->Setup())

        this->LoadScene(this->_sceneName);

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
    // Reload scene
    if (IO::Keyboard::Instance().IsKeyPressed(IO::Keyboard::Key::F4))
    {
        this->_scene->Reset();
        this->LoadScene(this->_sceneName);
        this->_scene->OnSceneSetup();
    }

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
    this->_scene->UpdateDebugInformation(this->_stats);
    this->_scene->Update(this->GetFrameDelta());
}

void Sandbox::SandboxApplication::OnUpdateFrame()
{
    this->_scene->Render();
}

void Sandbox::SandboxApplication::LoadScene(const std::string& name)
{
    try
    {
        Util::ResourcesLoader::Instance().LoadScene(reinterpret_cast<std::shared_ptr<Graphics::Scene>&>(this->_scene), name);
    } catch (const Core::Exception& e)
    {
        IO::Console::Instance().Error("Failed to load scene: %s\n", e.what());
    }
}

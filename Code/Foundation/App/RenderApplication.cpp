// ----------------------------------------------------------------------------------------
//  \file       RenderApplication.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "App/RenderApplication.h"
#include "Core/Debug.h"
#include "Graphics/Core.h"
#include "Graphics/Mesh.h"
#include "IO/Console.h"
#include "IO/Mouse.h"

App::RenderApplication::RenderApplication() :
    _stats({0, 0.0f}),
    _frameTime(0.0f),
    _currentSecond(0.0f),
    _frameCount(0),
    _lastFrameCount(0),
    _isQuitRequested(false),
    _vSyncEnabled(true),
    _wireframeModeEnabled(false)
{
}

bool App::RenderApplication::Open()
{
    _Assert(!this->IsOpen())

    if (Application::Open())
    {
        if (!Graphics::Core::Instance().Setup())
        {
            IO::Console::Instance().Error("Failed to initialize graphics core\n");
            return false;
        }

        this->_window = std::make_shared<Graphics::Window>(1280, 720, this->_title);
        this->_window->Create();

        if (!Graphics::Core::Instance().SetRenderingContext(this->_window))
        {
            IO::Console::Instance().Error("Failed to set rendering context\n");
            return false;
        }

        this->OnConfigureContext();

        return true;
    }

    return false;
}

void App::RenderApplication::Run()
{
    _Assert(this->IsOpen())

    // Reset timer
    this->_time = Timing::Time::Now();

    // Enter main loop
    while (!this->IsQuitRequested())
    {
        this->UpdateTiming();
        this->OnProcessInput();
        this->OnUpdateLogic();
        this->OnInitializeFrame();
        this->OnUpdateFrame();
        this->_window->SwapBuffers();
        glfwPollEvents();
    }
}

void App::RenderApplication::Close()
{
    _Assert(this->IsOpen())

    this->_window->Close();
    this->_window->Destroy();

    Graphics::Core::Instance().Destroy();

    Application::Close();
}

void App::RenderApplication::SetTitle(const std::string& title)
{
    Application::SetTitle(title);
    if (this->_window)
    {
        this->_window->SetTitle(title);
    }
}

void App::RenderApplication::OnConfigureContext()
{
    this->SetVSyncEnabled(true);

    glClearColor(0.2f, 0.325f, 0.375f, 1.0f);

    // Enable multi-sampling
    glEnable(GL_MULTISAMPLE);

    // Enable sRGB
    //glEnable(GL_FRAMEBUFFER_SRGB);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Enable CCW culling (counterclockwise)
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    // Enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Enable wireframe mode
    this->SetWireframeModeEnabled(false);

    this->_window->Open();
}

void App::RenderApplication::OnInitializeFrame()
{
    IO::Mouse::Instance().FlushMotion();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void App::RenderApplication::PrintDeviceInfo() const
{
    IO::Console::Instance().Info(
        "**************************************************\n"
        "Vendor name: %s\n"
        "Model name: %s\n"
        "Driver version: %s\n"
        "**************************************************\n",
        Graphics::Core::Instance().GetDeviceVendor().c_str(),
        Graphics::Core::Instance().GetDeviceName().c_str(),
        Graphics::Core::Instance().GetDriverVersion().c_str()
    );
}

void App::RenderApplication::SetVSyncEnabled(const bool enabled)
{
    if (this->_vSyncEnabled != enabled)
    {
        this->_vSyncEnabled = enabled;
        glfwSwapInterval(this->_vSyncEnabled ? 1 : 0);
    }
}

void App::RenderApplication::SetWireframeModeEnabled(const bool enabled)
{
    if (this->_wireframeModeEnabled != enabled)
    {
        this->_wireframeModeEnabled = enabled;
        if (this->_wireframeModeEnabled)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            Graphics::Mesh::SetCullingEnabled(false);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            Graphics::Mesh::SetCullingEnabled(true);
        }
    }
}

float App::RenderApplication::GetFrameDelta() const
{
    return std::chrono::duration_cast<Timing::Seconds>(this->_frameTime).count();
}

void App::RenderApplication::UpdateTiming()
{
    const Timing::Time now = Timing::Time::Now();

    this->_frameTime = now.Diff(this->_time);
    this->_time = now;

    if (this->_currentSecond > 999999.999f)
    {
        this->_stats = {
            this->_frameCount,
            this->_currentSecond / static_cast<float>(this->_frameCount) / 1000.0f
        };
        this->_lastFrameCount = this->_frameCount;
        this->_currentSecond = 0.0f;
        this->_frameCount = 0;
    }

    this->_currentSecond += this->_frameTime.count();
    this->_frameCount++;
}

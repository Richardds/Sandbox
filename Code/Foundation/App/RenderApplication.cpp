#include "RenderApplication.h"
#include "../Core/Debug.h"
#include "../Graphics/Core.h"
#include "../IO/Console.h"
#include "../IO/Mouse.h"

App::RenderApplication::RenderApplication() :
    _isQuitRequested(false),
    _frameTime(0)
{
}

App::RenderApplication::~RenderApplication()
{
    _assert(!this->IsOpen());
}

bool App::RenderApplication::Open()
{
    _assert(!this->IsOpen());

    if (Application::Open())
    {
        if (!Graphics::Core::Instance().Setup()) {
            IO::Console::Instance().Error("Failed to initialize graphics core\n");
            return false;
        }

        this->window = std::make_shared<Graphics::Window>(1280, 720, this->GetTitle());
        this->window->Create();

        if (!Graphics::Core::Instance().SetRenderingContext(this->window)) {
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
    _assert(this->IsOpen());

    while (!this->IsQuitRequested())
    {
        this->UpdateTime();
        this->OnProcessInput();
        this->OnUpdateLogic();
        this->OnInitializeFrame();
        this->OnUpdateFrame();
        this->window->SwapBuffers();
        glfwPollEvents();
    }
}

void App::RenderApplication::Close()
{
    _assert(this->IsOpen());

    this->window->Close();
    this->window->Destroy();

    Graphics::Core::Instance().Destroy();

    Application::Close();
}

void App::RenderApplication::OnConfigureContext()
{
    glEnable(GL_MULTISAMPLE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); 
    glFrontFace(GL_CCW);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    this->window->Open();
}

void App::RenderApplication::OnProcessInput()
{
    // Override
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

void App::RenderApplication::OnUpdateLogic()
{
    // Override
}

void App::RenderApplication::OnUpdateFrame()
{
    // Override
}

void App::RenderApplication::UpdateTime()
{
    Timing::Time now = Timing::Time::Now();

    this->_frameTime = now.Diff(this->_time);
    this->_time = Timing::Time::Now();
}

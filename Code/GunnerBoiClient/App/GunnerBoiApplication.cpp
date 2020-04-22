#include <Graphics/Core.h>
#include <IO/Keyboard.h>
#include <IO/Console.h>

#include "GunnerBoiApplication.h"

GunnerBoi::GunnerBoiApplication::GunnerBoiApplication()
{
}

GunnerBoi::GunnerBoiApplication::~GunnerBoiApplication()
{
}

bool GunnerBoi::GunnerBoiApplication::Open()
{
    if (RenderApplication::Open())
    {
        this->PrintStartupMessage();

        this->_scene = std::make_shared<Graphics::Scene>();
        _assert(this->_scene->Load());

        return true;
    }

    return false;
}

void GunnerBoi::GunnerBoiApplication::Close()
{
    RenderApplication::Close();
}

void GunnerBoi::GunnerBoiApplication::OnProcessInput()
{
    this->_scene->ProcessInput();
}

void GunnerBoi::GunnerBoiApplication::OnUpdateLogic()
{
    this->_scene->Update(this->_frameTime);
}

void GunnerBoi::GunnerBoiApplication::OnUpdateFrame()
{
    this->_scene->Render();
}

void GunnerBoi::GunnerBoiApplication::PrintStartupMessage()
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

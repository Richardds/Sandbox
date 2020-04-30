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
        this->PrintDeviceInfo();

        this->_scene = std::make_shared<GunnerBoiScene>();
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
    this->_scene->Update(this->GetFrameDelta());
}

void GunnerBoi::GunnerBoiApplication::OnUpdateFrame()
{
    this->_scene->Render();
}

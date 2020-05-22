#include "GunnerBoiApplication.h"
#include "IO/Keyboard.h"

bool GunnerBoi::GunnerBoiApplication::Open()
{
	if (RenderApplication::Open())
	{
		this->PrintDeviceInfo();

		this->_scene = std::make_shared<GunnerBoiScene>();
		_Assert(this->_scene->Setup());

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

void GunnerBoi::GunnerBoiApplication::OnUpdateLogic()
{
	this->_scene->Update(this->GetFrameDelta());
}

void GunnerBoi::GunnerBoiApplication::OnUpdateFrame()
{
	this->_scene->Render();
}

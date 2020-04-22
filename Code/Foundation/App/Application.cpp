#include "Application.h"
#include "../Core/Debug.h"

App::Application::Application() :
    _title("Application"),
    _version("1.0.0"),
    _isOpen(false),
    _statusCode(EXIT_SUCCESS)
{
}

App::Application::~Application()
{
    _assert(!this->IsOpen());
}

bool App::Application::Open()
{
    _assert(!this->IsOpen());
    this->_isOpen = true;
    return true;
}

void App::Application::Run()
{
    // Override
}

void App::Application::Close()
{
    _assert(this->IsOpen());
    this->_isOpen = false;
}

#include "Window.h"
#include "Core.h"

Graphics::Window::Window() :
    _isCreated(false),
    _width(1280),
    _height(720),
    _glfwWindow(nullptr)
{
}

Graphics::Window::Window(unsigned int width, unsigned int height, const std::string& title) :
    _isCreated(false),
    _width(width),
    _height(height),
    _title(title),
    _glfwWindow(nullptr)
{
}

Graphics::Window::~Window()
{
    _assert(!this->IsCreated());
}

bool Graphics::Window::Create()
{
    _assert(!this->IsCreated());
    _assert(Core::Instance().IsCreated());

    this->_glfwWindow = glfwCreateWindow(
        static_cast<int>(this->_width),
        static_cast<int>(this->_height),
        this->_title.c_str(),
        NULL,
        NULL
    );

    _assert(nullptr != this->_glfwWindow);

    this->_isCreated = true;

    return true;
}

void Graphics::Window::Open()
{
    glfwShowWindow(this->_glfwWindow);
}

void Graphics::Window::Close()
{
    glfwHideWindow(this->_glfwWindow);
}

void Graphics::Window::Destroy()
{
    _assert(this->IsCreated());

    glfwDestroyWindow(this->_glfwWindow);

    this->_isCreated = false;
}

void Graphics::Window::SwapBuffers()
{
    _assert(this->IsCreated());
    glfwSwapBuffers(this->_glfwWindow);
}

bool Graphics::Window::IsCloseRequested() const
{
    _assert(this->IsCreated());
    return glfwWindowShouldClose(this->_glfwWindow);
}

float Graphics::Window::GetAspectRatio() const
{
    return static_cast<float>(this->_width) / static_cast<float>(this->_height);
}

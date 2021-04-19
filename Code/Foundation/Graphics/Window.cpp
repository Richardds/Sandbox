// ----------------------------------------------------------------------------------------
//  \file       Window.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Graphics/Window.h"
#include "Graphics/Core.h"

Graphics::Window::Window() :
    Window(1280, 720, "")
{
}

Graphics::Window::Window(const unsigned int width, const unsigned int height, const std::string& title) :
    _isCreated(false),
    _fullScreenEnabled(false),
    _width(width),
    _height(height),
    _title(title),
    _glfwWindow(nullptr)
{
}

Graphics::Window::~Window()
{
    _Assert(!this->IsCreated())
}

bool Graphics::Window::Create()
{
    _Assert(!this->IsCreated())
    _Assert(Core::Instance().IsCreated())

    this->_glfwWindow = glfwCreateWindow(
        static_cast<int>(this->_width),
        static_cast<int>(this->_height),
        this->_title.c_str(),
        nullptr,
        nullptr
    );

    _Assert(nullptr != this->_glfwWindow)

    this->_isCreated = true;

    return true;
}

void Graphics::Window::Open() const
{
    glfwShowWindow(this->_glfwWindow);
}

void Graphics::Window::Close() const
{
    glfwHideWindow(this->_glfwWindow);
}

void Graphics::Window::Destroy()
{
    _Assert(this->IsCreated())

    glfwDestroyWindow(this->_glfwWindow);

    this->_isCreated = false;
}

void Graphics::Window::SwapBuffers() const
{
    _Assert(this->IsCreated())
    glfwSwapBuffers(this->_glfwWindow);
}

bool Graphics::Window::IsCloseRequested() const
{
    _Assert(this->IsCreated())
    return glfwWindowShouldClose(this->_glfwWindow);
}

float Graphics::Window::GetAspectRatio() const
{
    return static_cast<float>(this->_width) / static_cast<float>(this->_height);
}

void Graphics::Window::ApplyViewport() const
{
    _Assert(this->IsCreated())

    if (this->_fullScreenEnabled)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glViewport(0, 0, mode->width, mode->height);
    }
    else
    {
        glViewport(0, 0, this->_width, this->_height);
    }
}

void Graphics::Window::EnterFullScreen()
{
    if (!this->_fullScreenEnabled)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        this->_fullScreenEnabled = true;
        this->ApplyViewport();
        glfwSetWindowMonitor(
            this->_glfwWindow,
            monitor,
            0,
            0,
            mode->width,
            mode->height,
            mode->refreshRate
        );
    }
}

void Graphics::Window::ExitFullScreen()
{
    if (this->_fullScreenEnabled)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        this->_fullScreenEnabled = false;
        this->ApplyViewport();
        glfwSetWindowMonitor(
            this->_glfwWindow,
            nullptr,
            static_cast<int>(static_cast<float>(mode->width) / 2.0f - static_cast<float>(this->_width) / 2.0f),
            static_cast<int>(static_cast<float>(mode->height) / 2.0f - static_cast<float>(this->_height) / 2.0f),
            static_cast<int>(this->_width),
            static_cast<int>(this->_height),
            mode->refreshRate
        );
    }
}

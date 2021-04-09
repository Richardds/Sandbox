// ----------------------------------------------------------------------------------------
//  \file       Window.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Debug.h"

namespace Graphics
{
    /// GLFW context (window) class
    class EXPORT Window
    {
    public:
        Window();
        Window(unsigned int width, unsigned int height, const std::string& title);
        virtual ~Window();

        bool Create();
        void Open() const;
        void Close() const;
        void Destroy();
        void SwapBuffers() const;
        bool IsCloseRequested() const;
        bool IsCreated() const;
        void SetSize(unsigned int width, unsigned int height);
        unsigned int GetWidth() const;
        unsigned int GetHeight() const;
        float GetAspectRatio() const;
        void SetTitle(const std::string& title);
        const std::string& GetTitle() const;
        void ApplyViewport() const;
        void EnterFullScreen();
        void ExitFullScreen();
        GLFWwindow* GetGlfwWindow() const;

    private:
        bool _isCreated;
        bool _fullScreenEnabled;
        unsigned int _width;
        unsigned int _height;
        std::string _title;
        GLFWwindow* _glfwWindow;
    };

    inline bool Window::IsCreated() const
    {
        return this->_isCreated;
    }

    inline void Window::SetSize(const unsigned int width, const unsigned int height)
    {
        _Assert(0 < width)
        _Assert(0 < height)

        this->_width = width;
        this->_height = height;
    }

    inline unsigned int Window::GetWidth() const
    {
        return this->_width;
    }

    inline unsigned int Window::GetHeight() const
    {
        return this->_height;
    }

    inline void Window::SetTitle(const std::string& title)
    {
        this->_title = title;
        glfwSetWindowTitle(this->_glfwWindow, this->_title.c_str());
    }

    inline const std::string& Window::GetTitle() const
    {
        return this->_title;
    }

    inline GLFWwindow* Window::GetGlfwWindow() const
    {
        return this->_glfwWindow;
    }
}

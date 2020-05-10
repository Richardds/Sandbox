#pragma once

#include <memory>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Projection.h"
#include "../Core/Debug.h"
#include "../Game/Scene/Camera.h"

namespace Graphics
{

    class Window
    {
    public:
        Window();
        Window(unsigned int width, unsigned int height, const std::string& title);
        virtual ~Window();
        bool Create();
        void Open();
        void Close();
        void Destroy();
        void SwapBuffers();
        bool IsCloseRequested() const;
        bool IsCreated() const;
        void SetSize(unsigned int width, unsigned int height);
        unsigned int GetWidth() const;
        unsigned int GetHeight() const;
        float GetAspectRatio() const;
        void SetTitle(const std::string& title);
        const std::string& GetTitle() const;
        GLFWwindow* GetGlfwWindow() const;

    private:
        bool _isCreated;
        unsigned int _width;
        unsigned int _height;
        std::string _title;
        GLFWwindow* _glfwWindow;
    };

    inline bool Window::IsCreated() const
    {
        return this->_isCreated;
    }

    inline void Window::SetSize(unsigned int width, unsigned int height)
    {
        _assert(0 < width);
        _assert(0 < height);

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

#pragma once

#include <string>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Core/Singleton.h"
#include "Window.h"
#include "../Math/Vector.h"

namespace Graphics
{

    class Core
    {
        _Singleton(Core)

    public:
        Core();
        virtual ~Core();
        bool Setup();
        void Destroy();
        bool IsCreated() const;
        bool SetRenderingContext(std::shared_ptr<Window> window);
        std::shared_ptr<Window> GetRenderingContext() const;
        std::string GetGlString(GLenum name) const;
        Math::Vector4ui GetViewport() const;
        std::string GetDeviceVendor() const;
        std::string GetDeviceName() const;
        std::string GetDriverVersion() const;
        std::string GetGlDump() const;

        const int OPENGL_VERSION_MAJOR = 4;
        const int OPENGL_VERSION_MINOR = 3;

    private:
        static void glfwErrorCallback(int error, const char* description);
        static void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

        bool _isCreated;
        std::shared_ptr<Window> _context;
    };

    inline bool Core::IsCreated() const
    {
        return this->_isCreated;
    }

    inline std::shared_ptr<Window> Graphics::Core::GetRenderingContext() const
    {
        return this->_context;
    }

}

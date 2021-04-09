// ----------------------------------------------------------------------------------------
//  \file       Core.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Singleton.h"
#include "Graphics/Projection.h"
#include "Graphics/Window.h"
#include "Math/Vector.h"

namespace Graphics
{
    /// Helper singleton class for managing OpenGL low-level stuff
    class EXPORT Core
    {
    _Singleton(Core)

    public:
        Core();
        virtual ~Core();

        bool Setup();
        void Destroy();
        bool IsCreated() const;
        std::shared_ptr<Window> GetRenderingContext() const;
        bool SetRenderingContext(const std::shared_ptr<Window>& window);
        void Debug(const std::string& message);
        std::string GetGlString(GLenum name) const;
        Math::Vector4ui GetViewport() const;
        Math::Vector2f GetResolution() const;
        std::shared_ptr<Projection> MakeProjection(float fieldOfView) const;
        std::string GetDeviceVendor() const;
        std::string GetDeviceName() const;
        std::string GetDriverVersion() const;
        std::string GetGlDump() const;

        /// OpenGL major version
        const int OPENGL_VERSION_MAJOR = 4;
        /// OpenGL minor version
        const int OPENGL_VERSION_MINOR = 3;

    private:
        static void GlfwErrorCallback(int error, const char* description);
        static void APIENTRY GlDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                             const GLchar* message, const void* userParam);

        bool _isCreated;
        std::shared_ptr<Window> _context;
    };

    inline bool Core::IsCreated() const
    {
        return this->_isCreated;
    }

    inline std::shared_ptr<Window> Core::GetRenderingContext() const
    {
        return this->_context;
    }
}

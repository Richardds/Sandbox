#pragma once

#include <memory>
#include <string>

#include "Projection.h"
#include "Window.h"
#include "../Core/Singleton.h"
#include "../Core/Types.h"
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
		[[nodiscard]] bool IsCreated() const;
		[[nodiscard]] std::shared_ptr<Window> GetRenderingContext() const;
		bool SetRenderingContext(const std::shared_ptr<Window>& window);
		void Debug(const std::string& message);
		[[nodiscard]] std::string GetGlString(GLenum name) const;
		[[nodiscard]] Math::Vector4ui GetViewport() const;
		[[nodiscard]] std::shared_ptr<Projection> MakeProjection(float fieldOfView) const;
		[[nodiscard]] std::string GetDeviceVendor() const;
		[[nodiscard]] std::string GetDeviceName() const;
		[[nodiscard]] std::string GetDriverVersion() const;
		[[nodiscard]] std::string GetGlDump() const;

		const int OPENGL_VERSION_MAJOR = 4;
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

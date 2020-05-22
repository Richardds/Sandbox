#pragma once

#include "Precompiled.h"
#include "Graphics/ShaderProgram.h"

namespace Graphics
{
	class ShaderSystem : public ShaderProgram
	{
	public:
		enum class State
		{
			Initial,
			Shader,
			Ready
		};

		explicit ShaderSystem(std::string name);
		virtual ~ShaderSystem() = default;

		virtual void InitializeUniformVariables() = 0;
		bool Setup();
		void Use() override;

	protected:
		struct ClippingPlane
		{
			ClippingPlane() : plane(-1), enabled(-1)
			{
			}

			GLint plane;
			GLint enabled;
		};

		struct SunLocation
		{
			SunLocation() : direction(-1), ambient(-1), diffuse(-1), specular(-1)
			{
			}

			GLint direction;
			GLint ambient;
			GLint diffuse;
			GLint specular;
		};

		struct PointLightLocation
		{
			PointLightLocation() : position(-1), attenuation(-1), ambient(-1), diffuse(-1), specular(-1)
			{
			}

			GLint position;
			GLint attenuation;
			GLint ambient;
			GLint diffuse;
			GLint specular;
		};

		struct TextureSamplerLocation
		{
			TextureSamplerLocation() : texture(-1), enabled(-1)
			{
			}

			GLint texture;
			GLint enabled;
		};

		GLint GetUniformLocation(const std::string& name) override;
		void InitializeBoolLocation(const std::string& name, bool enabled, GLint& location);
		void InitializeIntLocation(const std::string& name, int value, GLint& location);
		void InitializeFloatLocation(const std::string& name, float value, GLint& location);
		void InitializeMatrix3fLocation(const std::string& name, const Math::Matrix3f& matrix, GLint& location);
		void InitializeMatrix4fLocation(const std::string& name, const Math::Matrix4f& matrix, GLint& location);
		void InitializeVector2fLocation(const std::string& name, const Math::Vector2f& vector, GLint& location);
		void InitializeVector3fLocation(const std::string& name, const Math::Vector3f& vector, GLint& location);
		void InitializeVector4fLocation(const std::string& name, const Math::Vector4f& vector, GLint& location);

	private:
		State _state;
		std::string _name;
		std::unordered_map<std::string, GLint> _uniformVariables;
	};
}

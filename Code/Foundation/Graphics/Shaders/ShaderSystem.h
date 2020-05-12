#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "../ShaderProgram.h"

namespace Graphics
{

    class ShaderSystem : public ShaderProgram
    {
    public:
        enum class State {
            INITIAL,
            SHADER,
            READY
        };

        ShaderSystem(const std::string& name);
        virtual ~ShaderSystem();
        virtual void InitializeUniformVariables() = 0;
        bool Setup();
        void Use();

    protected:
        struct ClippingPlane {
            ClippingPlane() : plane(-1), enabled(-1) {}
            GLint plane;
            GLint enabled;
        };

        struct SunLocation {
            SunLocation() : direction(-1), ambient(-1), diffuse(-1), specular(-1) {}
            GLint direction;
            GLint ambient;
            GLint diffuse;
            GLint specular;
        };

        struct PointLightLocation {
            PointLightLocation() : position(-1), attenuation(-1), ambient(-1), diffuse(-1), specular(-1) {}
            GLint position;
            GLint attenuation;
            GLint ambient;
            GLint diffuse;
            GLint specular;
        };

        struct TextureSamplerLocation {
            TextureSamplerLocation() : texture(-1), enabled(-1) {}
            GLint texture;
            GLint enabled;
        };

        GLint GetUniformLocation(const std::string& name);
        void InitializeBoolLocation(const std::string& name, bool enabled, GLint& location);
        void InitializeIntLocation(const std::string& name, int value, GLint& location);
        void InitializeFloatLocation(const std::string& name, float value, GLint& location);
        void InitializeMatrix3fLocation(const std::string& name, Math::Matrix3f matrix, GLint& location);
        void InitializeMatrix4fLocation(const std::string& name, Math::Matrix4f matrix, GLint& location);
        void InitializeVector3fLocation(const std::string& name, Math::Vector3f vector, GLint& location);
        void InitializeVector4fLocation(const std::string& name, Math::Vector4f vector, GLint& location);

    private:
        State _state;
        std::string _name;
        std::unordered_map<std::string, GLint> _uniformVariables;
    };

}

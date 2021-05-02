// ----------------------------------------------------------------------------------------
//  \file       ShaderSystem.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Graphics/ShaderProgram.h"

namespace Graphics
{
    /// Shader system base class operating over shader program
    class EXPORT ShaderSystem : public ShaderProgram
    {
    public:
        enum class State
        {
            Initial,
            Shader,
            Ready
        };

        explicit ShaderSystem(const std::string& name);

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

        struct DirectionalLightLocation
        {
            DirectionalLightLocation() : direction(-1), diffuse(-1), specular(-1)
            {
            }

            GLint direction;
            GLint diffuse;
            GLint intensity;
            GLint specular;
        };

        struct PointLightLocation
        {
            PointLightLocation() : position(-1), attenuation(-1), diffuse(-1), specular(-1)
            {
            }

            GLint position;
            GLint attenuation;
            GLint diffuse;
            GLint specular;
        };

        struct SpotLightLocation
        {
            SpotLightLocation() : position(-1), direction(-1), cutOff(-1), outerCutOff(-1), diffuse(-1), specular(-1)
            {
            }

            GLint position;
            GLint direction;
            GLint cutOff;
            GLint outerCutOff;
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

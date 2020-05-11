#pragma once

#include "ShaderSystem.h"
#include "../../Game/Scene/Camera.h"
#include "../../Game/Scene/Sun.h"
#include "../../Game/Scene/Light.h"
#include "../../Math/Matrix.h"
#include "../Projection.h"
#include "../Material.h"

namespace Graphics
{

    class WaterShader : public ShaderSystem
    {
    public:
        WaterShader();
        virtual ~WaterShader();
        void InitializeUniformVariables();
        void LoadProjection(std::shared_ptr<const Projection> projection);
        void LoadView(const std::shared_ptr<Camera>& view);
        void LoadSun(std::shared_ptr<Sun> sun);
        void LoadFog(float density, float gradient);
        void LoadWorldTransformation(const Math::Matrix4f& transformationMatrix);

    private:
        struct SunLocation {
            SunLocation() : direction(-1), ambient(-1), diffuse(-1), specular(-1) {}
            GLint direction;
            GLint ambient;
            GLint diffuse;
            GLint specular;
        };

        GLint _projectionLocation;
        GLint _viewLocation;
        GLint _viewInverseLocation;
        GLint _waterTransformationLocation;
        GLint _normalTransformationLocation;

        GLint _reflectionSamplerLocation;
        GLint _refractionSamplerLocation;

        SunLocation _sunLocation;

        GLint _fogDensityLocation;
        GLint _fogGradientLocation;
        GLint _fogColorLocation;

        Math::Matrix4f _viewMatrix;
    };

}

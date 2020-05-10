#pragma once

#include "ShaderSystem.h"

namespace Graphics
{

    class UIShader : public ShaderSystem
    {
    public:
        UIShader();
        virtual ~UIShader();
        void InitializeUniformVariables();
        void LoadTransformation(const Math::Matrix4f& transformation);

    private:
        GLuint _transformationLocation;
    };

}

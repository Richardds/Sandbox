#pragma once

#include "ShaderSystem.h"

namespace Graphics
{

    class DepthShader : public ShaderSystem
    {
    public:
        DepthShader();
        virtual ~DepthShader();
        void InitializeUniformVariables();
        void LoadTransformation(const Math::Matrix4f& transformation);
        
    private:
        GLint _transformationPosition;
    };

}

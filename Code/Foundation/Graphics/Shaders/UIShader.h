#pragma once

#include "ShaderSystem.h"
#include "../../Game/Camera.h"
#include "../../Game/Light.h"
#include "../../Math/Matrix.h"

namespace Graphics
{

    class UIShader : public ShaderSystem
    {
    public:
        UIShader();
        virtual ~UIShader();
        void Begin();
        void InitializeUniformVariables();
        void LoadUITransformation(const Math::Matrix4f& uiMatrix);

    private:
        GLuint _uiMatrixLocation;
    };

}

#pragma once

#include <memory>

#include "Shader.h"
#include "../Math/Matrix.h"
#include "../Math/Vector.h"

namespace Graphics
{

    class ShaderProgram
    {
    public:
        enum class State {
            INITIAL,
            ATTACHED,
            LINKED
        };

        ShaderProgram();
        virtual ~ShaderProgram();
        State GetState() const;
        void AttachRequiredShaders(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader);
        bool Link();
        virtual void Use();
        bool IsInUse() const;
        GLuint GetGlShaderProgram() const;
        std::shared_ptr<Shader> GetVertexShader() const;
        std::shared_ptr<Shader> GetFragmentShader() const;

        static GLuint GetInUse();

    protected:
        GLint GetUniformLocation(const std::string& name);
        void LoadBool(GLint location, bool enable);
        void LoadInt(GLint location, uint32_t value);
        void LoadFloat(GLint location, float value);
        void LoadMatrix3f(GLint location, const Math::Matrix3f& matrix);
        void LoadMatrix4f(GLint location, const Math::Matrix4f& matrix);
        void LoadVector2f(GLint location, const Math::Vector2f& vector);
        void LoadVector3f(GLint location, const Math::Vector3f& vector);
        void LoadVector4f(GLint location, const Math::Vector4f& vector);

    private:
        State _state;
        GLuint _glShaderProgram;
        std::shared_ptr<Shader> _vertexShader;
        std::shared_ptr<Shader> _fragmentShader;

        static GLuint _inUseGlShaderProgram;
    };

    inline Graphics::ShaderProgram::State Graphics::ShaderProgram::GetState() const
    {
        return this->_state;
    }

    inline bool Graphics::ShaderProgram::IsInUse() const
    {
        return ShaderProgram::_inUseGlShaderProgram == this->_glShaderProgram;
    }

    inline GLuint ShaderProgram::GetGlShaderProgram() const
    {
        return this->_glShaderProgram;
    }

    inline std::shared_ptr<Shader> ShaderProgram::GetVertexShader() const
    {
        return this->_vertexShader;
    }

    inline std::shared_ptr<Shader> ShaderProgram::GetFragmentShader() const
    {
        return this->_fragmentShader;
    }

    inline GLuint ShaderProgram::GetInUse()
    {
        return ShaderProgram::_inUseGlShaderProgram;
    }

}

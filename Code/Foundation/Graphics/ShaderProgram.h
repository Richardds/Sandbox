// ----------------------------------------------------------------------------------------
//  \file       ShaderProgram.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Graphics/Shader.h"
#include "Math/Matrix.h"
#include "Math/Vector.h"

namespace Graphics
{
    /// Low-level OpenGL shader program object wrapper
    class EXPORT ShaderProgram
    {
    public:
        enum class State
        {
            Initial,
            Attached,
            Linked
        };

        ShaderProgram();
        ShaderProgram(const ShaderProgram& shaderProgram) = delete;
        virtual ~ShaderProgram();

        ShaderProgram& operator=(const ShaderProgram& shaderProgram) = delete;

        State GetState() const;
        void AttachRequiredShaders(const std::shared_ptr<Shader>& vertexShader,
                                   const std::shared_ptr<Shader>& fragmentShader);
        bool Link();
        virtual void Use();
        bool IsInUse() const;
        GLuint GetGlShaderProgram() const;
        std::shared_ptr<Shader> GetVertexShader() const;
        std::shared_ptr<Shader> GetFragmentShader() const;

        static GLuint GetInUse();

    protected:
        virtual GLint GetUniformLocation(const std::string& name);
        void LoadBool(GLint location, bool enable) const;
        void LoadInt(GLint location, int32_t value) const;
        void LoadUInt(GLint location, uint32_t value) const;
        void LoadFloat(GLint location, float value) const;
        void LoadMatrix3f(GLint location, const Math::Matrix3f& matrix) const;
        void LoadMatrix4f(GLint location, const Math::Matrix4f& matrix) const;
        void LoadVector2f(GLint location, const Math::Vector2f& vector) const;
        void LoadVector3f(GLint location, const Math::Vector3f& vector) const;
        void LoadVector4f(GLint location, const Math::Vector4f& vector) const;

    private:
        State _state;
        GLuint _glShaderProgram;
        std::shared_ptr<Shader> _vertexShader;
        std::shared_ptr<Shader> _fragmentShader;

        static GLuint _inUseGlShaderProgram;
    };

    inline ShaderProgram::State ShaderProgram::GetState() const
    {
        return this->_state;
    }

    inline bool ShaderProgram::IsInUse() const
    {
        return _inUseGlShaderProgram == this->_glShaderProgram;
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
        return _inUseGlShaderProgram;
    }
}

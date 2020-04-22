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
        bool Load();
        void Use();
        virtual void Begin();

    protected:
        GLint GetUniformLocation(const std::string& name);

    private:
        State _state;
        std::string _name;
        std::unordered_map<std::string, GLint> _uniformVariables;
    };

}

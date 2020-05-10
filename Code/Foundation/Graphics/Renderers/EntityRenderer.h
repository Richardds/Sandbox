#pragma once

#include "../Shaders/EntityShader.h"
#include "../../Game/Scene/Sun.h"
#include "../../Game/Scene/Light.h"
#include "../../Game/Scene/Entity.h"
#include "../Projection.h"

namespace Graphics
{

    class EntityRenderer
    {
    public:
        enum class State {
            INITIAL,
            READY
        };

        EntityRenderer();
        virtual ~EntityRenderer();
        bool Setup(std::shared_ptr<const Projection> projection);
        void Begin(std::shared_ptr<Camera> camera, std::shared_ptr<Sun> sun, const std::unordered_map<std::string, std::shared_ptr<Light>>& lights);
        void Render(std::shared_ptr<Entity> entity);

    private:
        State _state;
        std::shared_ptr<EntityShader> _shader;
    };

}

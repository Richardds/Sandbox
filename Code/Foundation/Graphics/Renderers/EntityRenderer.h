#pragma once

#include "../Shaders/EntityShader.h"
#include "../../Game/Scene/PointLight.h"
#include "../../Game/Scene/DirectionalLight.h"
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
        std::shared_ptr<EntityShader> GetShader() const;
        bool Setup(std::shared_ptr<const Projection> projection);
        void Begin(std::shared_ptr<Camera> camera, std::shared_ptr<DirectionalLight> sun, const std::unordered_map<std::string, std::shared_ptr<PointLight>>& lights);
        void Render(std::shared_ptr<Entity> entity);

    private:
        State _state;
        std::shared_ptr<EntityShader> _shader;
    };

    inline std::shared_ptr<EntityShader> Graphics::EntityRenderer::GetShader() const
    {
        return this->_shader;
    }

}

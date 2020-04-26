#pragma once

#include <unordered_map>
#include <string>

#include "Shaders/EntityShader.h"
#include "Scene/TargetedCamera.h"
#include "Scene/Light.h"
#include "Scene/Entity.h"
#include "../Timing/Time.h"

namespace Graphics
{

    class Scene
    {
    public:
        enum class State {
            INITIAL,
            RUN
        };

        Scene();
        virtual ~Scene();
        State GetState() const;
        virtual bool Load();
        virtual void ProcessInput();
        virtual void Update(Timing::Duration delta);
        virtual void Render();

    protected:
        std::shared_ptr<Graphics::Light> AddLight(const std::string& lightName);
        std::shared_ptr<Graphics::Entity> AddEntity(const std::string& entityName, const std::string& resourceName);

        std::shared_ptr<EntityShader> _entityShader;
        std::shared_ptr<Graphics::TargetedCamera> _camera;
        std::unordered_map<std::string, std::shared_ptr<Light>> _lights;
        std::unordered_map<std::string, std::shared_ptr<Entity>> _entities;

    private:
        State _state;
    };

}

#pragma once

#include <unordered_map>
#include <string>

#include "../Graphics/Renderers/EntityRenderer.h"
#include "../Graphics/Renderers/WaterRenderer.h"
#include "../Timing/Time.h"
#include "Scene/TargetedCamera.h"
#include "Scene/Sun.h"
#include "Scene/Light.h"
#include "Scene/Entity.h"
#include "Scene/Water.h"

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
        virtual bool Setup();
        virtual void ProcessInput();
        virtual void Update(float delta);
        virtual void Render();
        Math::Vector3f GetScreenWorldPosition(Math::Vector2ui screenPosition) const;

    protected:
        virtual void RenderEntities();
        std::shared_ptr<Graphics::Water> AddWater(const std::string& name, float size);
        std::shared_ptr<Graphics::Light> AddLight(const std::string& name);
        std::shared_ptr<Graphics::Entity> AddEntity(const std::string& name, const std::string& resourceName);

        std::shared_ptr<Graphics::TargetedCamera> _camera;
        std::shared_ptr<EntityRenderer> _entityRenderer;
        std::shared_ptr<WaterRenderer> _waterRenderer;
        std::shared_ptr<Sun> _sun;
        std::unordered_map<std::string, std::shared_ptr<Water>> _waterTiles;
        std::unordered_map<std::string, std::shared_ptr<Light>> _lights;
        std::unordered_map<std::string, std::shared_ptr<Entity>> _entities;

    private:
        State _state;
    };

}

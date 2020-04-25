#pragma once

#include "Shaders/EntityShader.h"
#include "Shaders/UIShader.h"
#include "Scene/Player.h"
#include "Scene/TargetedCamera.h"
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
        bool Load();
        void ProcessInput();
        void Update(Timing::Duration delta);
        void Render();

    private:
        State _state;
        std::shared_ptr<Player> _player;
        std::shared_ptr<TargetedCamera> _camera;
        std::shared_ptr<EntityShader> _entityShader;
        std::vector<std::shared_ptr<Light>> _lights;
        std::vector<std::shared_ptr<Entity>> _entities;

        // UI
        std::shared_ptr<UIShader> _uiShader;
        std::shared_ptr<Model> _quad;
    };

}

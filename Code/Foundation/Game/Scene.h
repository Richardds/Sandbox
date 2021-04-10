// ----------------------------------------------------------------------------------------
//  \file       Scene.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/Renderers/SkyboxRenderer.h"
#include "Graphics/Renderers/EntityRenderer.h"
#include "Graphics/Renderers/WaterRenderer.h"
#include "Graphics/Renderers/TextRenderer.h"
#include "Game/Scene/Light/DirectionalLight.h"
#include "Game/Scene/Object/Entity.h"
#include "Game/Scene/Light/PointLight.h"
#include "Game/Scene/Object/Skybox.h"
#include "Game/Scene/Camera/TargetedCamera.h"
#include "Game/Scene/Object/Water.h"

namespace Graphics
{
    /// 3D scene which describe models, lights, camera and skybox
    class EXPORT Scene
    {
    public:
        enum class State
        {
            Initial,
            Run
        };

        Scene();
        virtual ~Scene() = default;

        State GetState() const;
        virtual bool Setup();
        virtual void ProcessInput();
        virtual void Update(float delta);
        virtual void Render();

    protected:
        virtual void RenderEntities();
        void RenderSkybox() const;
        Math::Vector3f GetScreenWorldPosition(const Math::Vector2ui& screenPosition) const;
        std::shared_ptr<Skybox> SetupSkybox(const std::string& name, float size) const;
        std::shared_ptr<Water> AddWater(const std::string& name, float size);
        std::shared_ptr<PointLight> AddLight(const std::string& name);
        std::shared_ptr<Entity> AddEntity(const std::string& name, const std::string& resourceName);
        std::shared_ptr<Entity> AddEntity(const std::string& name, const std::shared_ptr<Entity>& entity);

        std::shared_ptr<Projection> _projection;
        std::shared_ptr<TargetedCamera> _camera;
        std::shared_ptr<SkyboxRenderer> _skyboxRenderer;
        std::shared_ptr<EntityRenderer> _entityRenderer;
        std::shared_ptr<WaterRenderer> _waterRenderer;
        std::shared_ptr<TextRenderer> _textRenderer;
        std::shared_ptr<DirectionalLight> _sun;
        std::shared_ptr<Skybox> _skybox;
        std::unordered_map<std::string, std::shared_ptr<PointLight>> _lights;
        std::shared_ptr<SpotLight> _flashLight;
        std::unordered_map<std::string, std::shared_ptr<Entity>> _entities;
        std::unordered_map<std::string, std::shared_ptr<Water>> _waterTiles;

        Math::Vector3f _cursorPosition;
        float _time;
        bool _renderSkybox;
        bool _paused;

    private:
        State _state;
    };
}

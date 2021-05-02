// ----------------------------------------------------------------------------------------
//  \file       SceneLoader.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Game/Scene.h"
#include "IO/InputFile.h"
#include "Util/YAMLParser.h"

namespace Util
{
    /// Loader to populate scene from YAML config
    class EXPORT SceneLoader final : public YAMLParser
    {
    public:
        SceneLoader() = default;

        void Load(std::shared_ptr<Graphics::Scene>& scene, IO::InputFile& sceneFile);

    private:
        static const int SUPPORTED_VERSION = 1;

        void HandleScene(const YAML::Node& sceneNode) const;
        void HandleSkybox(const YAML::Node& skyboxNode) const;
        void HandleEntities(const YAML::Node& entitiesNode) const;
        void HandleEntity(const YAML::Node& entityNode) const;
        void HandleLights(const YAML::Node& lightsNode) const;
        void HandleDirectionalLights(const YAML::Node& directionalLightsNode) const;
        void HandleDirectionalLight(const YAML::Node& directionalLightNode) const;
        void HandlePointLights(const YAML::Node& pointLightsNode) const;
        void HandlePointLight(const YAML::Node& pointLightNode) const;

        std::shared_ptr<Graphics::Scene> _scene;
    };
}

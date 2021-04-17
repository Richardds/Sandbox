// ----------------------------------------------------------------------------------------
//  \file       SceneLoader.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Game/Scene.h"
#include "IO/InputFile.h"

namespace Util
{
    /// Loader to populate scene from YAML config
    class EXPORT SceneLoader final
    {
    public:
        SceneLoader();

        void Load(std::shared_ptr<Graphics::Scene>& scene, IO::InputFile& sceneFile);

    private:
        static const int SUPPORTED_VERSION = 1;

        static void ValidateNode(const YAML::Node& node, YAML::NodeType::value type);
        template<typename T>
        static T Parse(const YAML::Node& node);
        static Math::Vector2f ParseVector2f(const YAML::Node& node);
        static Math::Vector3f ParseVector3f(const YAML::Node& node);

        void HandleVersion(const YAML::Node& versionNode);
        void HandleScene(const YAML::Node& sceneNode) const;
        void HandleSkybox(const YAML::Node& skyboxNode) const;
        void HandleEntities(const YAML::Node& entitiesNode) const;
        void HandleEntity(const YAML::Node& entityNode) const;
        void HandleLights(const YAML::Node& lightsNode) const;
        void HandlePointLights(const YAML::Node& pointLightsNode) const;
        void HandlePointLight(const YAML::Node& pointLightNode) const;

        std::shared_ptr<Graphics::Scene> _scene;
        int _version;
    };

    template <typename T>
    T SceneLoader::Parse(const YAML::Node& node)
    {
        ValidateNode(node, YAML::NodeType::Scalar);

        return node.as<T>();
    }
}

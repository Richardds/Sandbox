// ----------------------------------------------------------------------------------------
//  \file       SceneLoader.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Util/Loaders/SceneLoader.h"
#include "Core/Exception/ParsingException.h"
#include "Core/Exception/UnsupportedException.h"
#include "IO/Console.h"
#include "Util/ResourcesLoader.h"

Util::SceneLoader::SceneLoader() :
    _version(0)
{
}

void Util::SceneLoader::Load(std::shared_ptr<Graphics::Scene>& scene, IO::InputFile& sceneFile)
{
    _Assert(scene)
    _Assert(sceneFile.IsOpen())

    YAML::Node root = YAML::Load(sceneFile.GetStream());

    ValidateNode(root, YAML::NodeType::Map);

    // Parse scene config version
    this->HandleVersion(root["version"]);

    // Parse scene
    this->_scene = scene;
    this->HandleScene(root["scene"]);    
}

void Util::SceneLoader::ValidateNode(const YAML::Node& node, const YAML::NodeType::value type)
{
    if (!node)
    {
        throw Core::ParsingException("Invalid node");
    }
    if (node.Type() != type)
    {
        throw Core::ParsingException("Invalid node type");
    }
}

Math::Vector2f Util::SceneLoader::ParseVector2f(const YAML::Node& node)
{
    ValidateNode(node, YAML::NodeType::Sequence);

    return Math::Vector2f(
        Parse<float>(node[0]),
        Parse<float>(node[1])
    );
}

Math::Vector3f Util::SceneLoader::ParseVector3f(const YAML::Node& node)
{
    ValidateNode(node, YAML::NodeType::Sequence);

    return Math::Vector3f(
        Parse<float>(node[0]),
        Parse<float>(node[1]),
        Parse<float>(node[2])
    );
}

void Util::SceneLoader::HandleVersion(const YAML::Node& versionNode)
{
    ValidateNode(versionNode, YAML::NodeType::Scalar);

    this->_version = versionNode.as<int>();
    if (SUPPORTED_VERSION != this->_version)
    {
        throw Core::UnsupportedException("Unsupported scene format");
    }
}

void Util::SceneLoader::HandleScene(const YAML::Node& sceneNode) const
{
    ValidateNode(sceneNode, YAML::NodeType::Map);

    // Parse optional skybox
    if (sceneNode["skybox"])
    {
        this->HandleSkybox(sceneNode["skybox"]);
    }

    // Parse entities
    this->HandleEntities(sceneNode["entities"]);

    // Parse lights
    this->HandleLights(sceneNode["lights"]);
}

void Util::SceneLoader::HandleSkybox(const YAML::Node& skyboxNode) const
{
    ValidateNode(skyboxNode, YAML::NodeType::Map);

    // Parse required name
    const std::string name = Parse<std::string>(skyboxNode["name"]);

    // Parse required size
    const float size = Parse<float>(skyboxNode["size"]);
    
    this->_scene->SetupSkybox(name, size);
}

void Util::SceneLoader::HandleEntities(const YAML::Node& entitiesNode) const
{
    ValidateNode(entitiesNode, YAML::NodeType::Sequence);
    
    for (const auto& entityNode : entitiesNode)
    {
        this->HandleEntity(entityNode);
    }
}

void Util::SceneLoader::HandleEntity(const YAML::Node& entityNode) const
{
    ValidateNode(entityNode, YAML::NodeType::Map);

    // Parse required model identifier
    const std::string model = Parse<std::string>(entityNode["model"]);

    // Parse optional name
    std::shared_ptr<Graphics::Entity> entity;
    if (entityNode["name"])
    {
        entity = this->_scene->AddEntity(Parse<std::string>(entityNode["name"]), model);
    } else
    {
        entity = this->_scene->AddEntity(model);
    }

    // Parse optional position
    if (entityNode["position"])
    {
        entity->SetPosition(ParseVector3f(entityNode["position"]));
    }

    // Parse optional rotation
    if (entityNode["rotation"])
    {
        entity->SetRotation(ParseVector3f(entityNode["rotation"]));
    }

    // Parse optional scale
    if (entityNode["scale"])
    {
        entity->SetScale(Parse<float>(entityNode["scale"]));
    }
}

void Util::SceneLoader::HandleLights(const YAML::Node& lightsNode) const
{
    ValidateNode(lightsNode, YAML::NodeType::Map);

    // Parse point lights
    this->HandlePointLights(lightsNode["point"]);

    // TODO: Other light types
}

void Util::SceneLoader::HandlePointLights(const YAML::Node& pointLightsNode) const
{
    ValidateNode(pointLightsNode, YAML::NodeType::Sequence);

    for (const auto& pointLightNode : pointLightsNode)
    {
        this->HandlePointLight(pointLightNode);
    }
}

void Util::SceneLoader::HandlePointLight(const YAML::Node& pointLightNode) const
{
    ValidateNode(pointLightNode, YAML::NodeType::Map);

    std::shared_ptr<Graphics::PointLight> light;

    // Parse optional name
    if (pointLightNode["name"])
    {
        light = this->_scene->AddLight(Parse<std::string>(pointLightNode["name"]));
    } else
    {
        light = this->_scene->AddLight();
    }

    // Parse optional position
    if (pointLightNode["position"])
    {
        light->SetPosition(ParseVector3f(pointLightNode["position"]));
    }

    // Parse optional intensity
    if (pointLightNode["intensity"])
    {
        light->SetIntensity(Parse<float>(pointLightNode["intensity"]));
    }

    // Parse optional color
    if (pointLightNode["color"])
    {
        light->SetColor(ParseVector3f(pointLightNode["color"]));
    }

    // Parse optional attenuation
    if (pointLightNode["attenuation"])
    {
        light->SetAttenuation(ParseVector3f(pointLightNode["attenuation"]));
    }
}

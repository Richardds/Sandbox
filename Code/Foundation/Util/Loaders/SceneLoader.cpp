// ----------------------------------------------------------------------------------------
//  \file       SceneLoader.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Util/Loaders/SceneLoader.h"
#include "Core/Exception/ParsingException.h"
#include "Util/ResourcesLoader.h"

void Util::SceneLoader::Load(std::shared_ptr<Graphics::Scene>& scene, IO::InputFile& sceneFile)
{
    _Assert(scene)
    _Assert(sceneFile.IsOpen())

    YAML::Node root = YAML::Load(sceneFile.GetStream());

    this->ValidateNode(root, YAML::NodeType::Map);

    // Parse scene config version
    this->ValidateVersion(root["version"], SUPPORTED_VERSION);

    // Parse scene
    this->_scene = scene;
    this->HandleScene(root["scene"]);    
}

void Util::SceneLoader::HandleScene(const YAML::Node& sceneNode) const
{
    this->ValidateNode(sceneNode, YAML::NodeType::Map);

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
    this->ValidateNode(skyboxNode, YAML::NodeType::Map);

    // Parse required name
    const std::string name = this->Parse<std::string>(skyboxNode["name"]);

    // Parse required size
    const float size = this->Parse<float>(skyboxNode["size"]);
    
    this->_scene->SetupSkybox(name, size);
}

void Util::SceneLoader::HandleEntities(const YAML::Node& entitiesNode) const
{
    this->ValidateNode(entitiesNode, YAML::NodeType::Sequence);
    
    for (const auto& entityNode : entitiesNode)
    {
        this->HandleEntity(entityNode);
    }
}

void Util::SceneLoader::HandleEntity(const YAML::Node& entityNode) const
{
    this->ValidateNode(entityNode, YAML::NodeType::Map);

    // Parse required model identifier
    const std::string model = this->Parse<std::string>(entityNode["model"]);

    // Parse optional name
    std::shared_ptr<Graphics::Entity> entity;
    if (entityNode["name"])
    {
        entity = this->_scene->AddEntity(this->Parse<std::string>(entityNode["name"]), model);
    } else
    {
        entity = this->_scene->AddEntity(model);
    }

    // Parse optional position
    if (entityNode["position"])
    {
        entity->SetPosition(this->ParseVector3f(entityNode["position"]));
    }

    // Parse optional rotation
    if (entityNode["rotation"])
    {
        entity->SetRotation(this->ParseVector3f(entityNode["rotation"]));
    }

    // Parse optional scale
    if (entityNode["scale"])
    {
        entity->SetScale(this->Parse<float>(entityNode["scale"]));
    }

    // Parse optional culling
    if (entityNode["culling"])
    {
        const bool culling = this->Parse<bool>(entityNode["culling"]);
        // Temporary solution to set culling on all model meshes
        for (const auto& [name, mesh] : entity->GetModel()->GetMeshes())
        {
            mesh->SetCulling(culling);
        }
    }
}

void Util::SceneLoader::HandleLights(const YAML::Node& lightsNode) const
{
    ValidateNode(lightsNode, YAML::NodeType::Map);

    // Parse directional lights
    this->HandleDirectionalLights(lightsNode["directional"]);

    // Parse point lights
    this->HandlePointLights(lightsNode["point"]);
}

void Util::SceneLoader::HandleDirectionalLights(const YAML::Node& directionalLightsNode) const
{
    ValidateNode(directionalLightsNode, YAML::NodeType::Sequence);

    for (const auto& directionalLightNode : directionalLightsNode)
    {
        this->HandleDirectionalLight(directionalLightNode);
    }
}

void Util::SceneLoader::HandleDirectionalLight(const YAML::Node& directionalLightNode) const
{
    this->ValidateNode(directionalLightNode, YAML::NodeType::Map);

    std::shared_ptr<Graphics::DirectionalLight> light;

    // Parse optional name
    if (directionalLightNode["name"])
    {
        light = this->_scene->AddDirectionalLight(this->Parse<std::string>(directionalLightNode["name"]));
    } else
    {
        light = this->_scene->AddDirectionalLight();
    }

    // Parse optional position
    if (directionalLightNode["direction"])
    {
        light->SetDirection(this->ParseVector3f(directionalLightNode["direction"]));
    }

    // Parse optional intensity
    if (directionalLightNode["intensity"])
    {
        light->SetIntensity(this->Parse<float>(directionalLightNode["intensity"]));
    }

    // Parse optional color
    if (directionalLightNode["color"])
    {
        light->SetColor(this->ParseVector3f(directionalLightNode["color"]));
    }
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
    this->ValidateNode(pointLightNode, YAML::NodeType::Map);

    std::shared_ptr<Graphics::PointLight> light;

    // Parse optional name
    if (pointLightNode["name"])
    {
        light = this->_scene->AddLight(this->Parse<std::string>(pointLightNode["name"]));
    } else
    {
        light = this->_scene->AddLight();
    }

    // Parse optional position
    if (pointLightNode["position"])
    {
        light->SetPosition(this->ParseVector3f(pointLightNode["position"]));
    }

    // Parse optional intensity
    if (pointLightNode["intensity"])
    {
        light->SetIntensity(this->Parse<float>(pointLightNode["intensity"]));
    }

    // Parse optional color
    if (pointLightNode["color"])
    {
        light->SetColor(this->ParseVector3f(pointLightNode["color"]));
    }

    // Parse optional attenuation
    if (pointLightNode["attenuation"])
    {
        light->SetAttenuation(this->ParseVector3f(pointLightNode["attenuation"]));
    }
}

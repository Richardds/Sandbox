#pragma once

#include <unordered_map>
#include <string>

#include "../Core/Singleton.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Model.h"

namespace Util
{

    class ResourcesLoader
    {
        _Singleton(ResourcesLoader)

    public:
        ResourcesLoader();
        virtual ~ResourcesLoader();
        std::string GetResourcesRoot() const;
        void SetResourcesRoot(const std::string& root);
        std::shared_ptr<Graphics::Shader> LoadShader(const std::string& name, GLenum type);
        std::shared_ptr<Graphics::Texture> LoadTexture(const std::string& name);
        std::shared_ptr<Graphics::Model> LoadModel(const std::string& name);

    private:
        std::string _root;
        std::unordered_map<std::string, std::shared_ptr<Graphics::Texture>> _textures;
        std::unordered_map<std::string, std::shared_ptr<Graphics::Model>> _models;
    };

    inline std::string Util::ResourcesLoader::GetResourcesRoot() const
    {
        return this->_root;
    }

    inline void Util::ResourcesLoader::SetResourcesRoot(const std::string& root)
    {
        this->_root = root;
    }

}

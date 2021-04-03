// ----------------------------------------------------------------------------------------
//  \file       ResourcesLoader.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Singleton.h"
#include "Graphics/FontType.h"
#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

namespace Util
{
    /// Global resource loader for loading models and textures
    /// Handles caching and reusing of already loaded models
    class ResourcesLoader
    {
    _Singleton(ResourcesLoader)

    public:
        ResourcesLoader();
        [[nodiscard]] std::string GetResourcesRoot() const;
        void SetResourcesRoot(const std::string& root);
        [[nodiscard]] std::shared_ptr<Graphics::Shader> LoadShader(const std::string& name, GLenum type) const;
        [[nodiscard]] std::shared_ptr<Graphics::Texture> LoadTexture(const std::string& name, GLenum target = GL_TEXTURE_2D);
        [[nodiscard]] std::shared_ptr<Graphics::Texture> LoadCubeMap(const std::string& name);
        [[nodiscard]] std::shared_ptr<Graphics::FontType> LoadFont(const std::string& name);
        [[nodiscard]] std::shared_ptr<Graphics::Model> LoadFBX(const std::string& name);
        [[nodiscard]] std::shared_ptr<Graphics::Model> LoadModel(const std::string& name);

    private:
        std::string _root;
        std::unordered_map<std::string, std::shared_ptr<Graphics::Texture>> _textures;
        std::unordered_map<std::string, std::shared_ptr<Graphics::Model>> _models;
    };

    inline std::string ResourcesLoader::GetResourcesRoot() const
    {
        return this->_root;
    }

    inline void ResourcesLoader::SetResourcesRoot(const std::string& root)
    {
        this->_root = root;
    }
}

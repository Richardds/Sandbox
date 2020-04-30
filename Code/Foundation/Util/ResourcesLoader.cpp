#include <fstream>
#include <string>

#include "ResourcesLoader.h"
#include "../Core/Debug.h"
#include "../IO/Console.h"
#include "../Math/Vector.h"
#include "Loaders/AssimpLoader.h"
#include "Loaders/DirectDrawSurfaceLoader.h"

Util::ResourcesLoader::ResourcesLoader() :
    _root("Resources")
{
}

Util::ResourcesLoader::~ResourcesLoader()
{
}

std::shared_ptr<Graphics::Shader> Util::ResourcesLoader::LoadShader(const std::string& name, GLenum type)
{
    const std::string type_str = Graphics::Shader::GetStringFromType(type);

    IO::Console::Instance().Info("Loading %s shader '%s'\n", type_str.c_str(), name.c_str());

    std::shared_ptr<Graphics::Shader> shader = std::make_shared<Graphics::Shader>(type);

    const std::string path = this->_root + "/Shaders/" + name + "/" + name + "." + Graphics::Shader::GetExtensionFromType(type);

    std::ifstream shaderFile(path, std::ios::binary | std::ios::ate);
    if (!shaderFile.is_open()) {
        IO::Console::Instance().Warning("Failed to open %s shader '%s'\n", type_str.c_str(), name.c_str());
        return shader;
    }

    std::streamsize shaderFileSize = shaderFile.tellg();
    if (shaderFileSize == 0) {
        shaderFile.close();
        IO::Console::Instance().Warning("Failed to load %s shader '%s'\n", type_str.c_str(), name.c_str());
        return shader;
    }

    shaderFile.seekg(0, std::ios::beg);

    std::vector<char> shaderSource(shaderFileSize + 1);
    shaderFile.read(shaderSource.data(), shaderFileSize);
    shaderFile.close();

    shaderSource[shaderFileSize] = '\0';
    shader->SetSource(shaderSource.data());

    return shader;
}

std::shared_ptr<Graphics::Texture> Util::ResourcesLoader::LoadTexture(const std::string& name)
{
    auto it = this->_textures.find(name);
    if (it != this->_textures.end()) {
        return it->second;
    }

    IO::Console::Instance().Info("Loading texture '%s'\n", name.c_str());

    std::shared_ptr<Graphics::Texture> texture = std::make_shared<Graphics::Texture>();

    std::string path = this->_root + "/Textures/" + name + ".dds";

    std::ifstream textureFile(path, std::ios::binary | std::ios::ate);
    if (!textureFile.is_open()) {
        IO::Console::Instance().Warning("Failed to open texture '%s'\n", name.c_str());
        return texture;
    }

    std::streamsize TextureFileSize = textureFile.tellg();
    if (TextureFileSize == 0) {
        IO::Console::Instance().Warning("Failed to load texture '%s'\n", name.c_str());
        return texture;
    }
    textureFile.seekg(0, std::ios::beg);

    std::vector<char> buffer(TextureFileSize);
    textureFile.read(buffer.data(), TextureFileSize);
    textureFile.close();

    DirectDrawSurfaceLoader loader;
    texture = loader.Load(buffer);

    this->_textures.emplace(name, texture);

    return texture;
}

std::shared_ptr<Graphics::Model> Util::ResourcesLoader::LoadModel(const std::string& name)
{
    auto it = this->_models.find(name);
    if (it != this->_models.end()) {
        return it->second;
    }

    IO::Console::Instance().Info("Loading model '%s'\n", name.c_str());

    std::shared_ptr<Graphics::Model> model = std::make_shared<Graphics::Model>();

    const std::string path = this->_root + "/Models/" + name + ".fbx";

    std::ifstream modelFile(path, std::ios::binary | std::ios::ate);
    if (!modelFile.is_open()) {
        IO::Console::Instance().Warning("Failed to open model '%s'\n", name.c_str());
        return model;
    }

    std::streamsize modelFileSize = modelFile.tellg();
    if (modelFileSize == 0) {
        IO::Console::Instance().Warning("Failed to load model '%s': Model file is empty\n", name.c_str());
        return model;
    }
    modelFile.seekg(0, std::ios::beg);

    std::vector<char> buffer(modelFileSize);
    modelFile.read(buffer.data(), modelFileSize);
    modelFile.close();

    AssimpLoader loader;
    
    try {
        model = loader.Load(buffer);
    }
    catch (const std::runtime_error& e) {
        IO::Console::Instance().Warning("Failed to load model '%s': %s\n", name.c_str(), e.what());
        return model;
    }

    this->_models.emplace(name, model);

    return model;
}

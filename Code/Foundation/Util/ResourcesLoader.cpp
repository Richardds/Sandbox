// ----------------------------------------------------------------------------------------
//  \file       ResourcesLoader.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Util/ResourcesLoader.h"
#include "IO/Console.h"
#include "Loaders/FontMappingLoader.h"
#include "Loaders/SceneLoader.h"
#include "Util/Loaders/DirectDrawSurfaceLoader.h"
#include "Util/Loaders/ModelLoader.h"

Util::ResourcesLoader::ResourcesLoader() :
    _root("Resources")
{
}

std::shared_ptr<Graphics::Shader> Util::ResourcesLoader::LoadShader(const std::string& name, GLenum type) const
{
    const std::string type_str = Graphics::Shader::GetStringFromType(type);

    IO::Console::Instance().Info("Loading '%s' %s shader\n", name.c_str(), type_str.c_str());

    std::shared_ptr<Graphics::Shader> shader = std::make_shared<Graphics::Shader>(type);

    const std::string path = this->_root + "/Shaders/" + name + "/" + name + "." +
        Graphics::Shader::GetExtensionFromType(type);

    IO::InputFile shaderFile(path);
    if (!shaderFile.IsOpen())
    {
        IO::Console::Instance().Error("Failed to open %s shader '%s'\n", type_str.c_str(), name.c_str());
        return shader;
    }
    if (shaderFile.IsEmpty())
    {
        IO::Console::Instance().Error("Failed to load shader '%s': Shader file is empty\n", name.c_str());
        shaderFile.Close();
        return shader;
    }

    // Read shader into memory
    const size_t shaderFileSize = shaderFile.GetSize();
    std::vector<char> shaderSource(shaderFileSize);
    shaderFile.Read(shaderSource.data(), shaderFileSize);

    shaderFile.Close();
    
    shader->SetSource(std::string(shaderSource.begin(), shaderSource.end()));

    return shader;
}

std::shared_ptr<Graphics::Texture> Util::ResourcesLoader::LoadTexture(const std::string& name, const GLenum target)
{
    const auto it = this->_textures.find(name);
    if (it != this->_textures.end())
    {
        return it->second;
    }

    IO::Console::Instance().Info("Loading '%s' texture\n", name.c_str());

    std::shared_ptr<Graphics::Texture> texture = std::make_shared<Graphics::Texture>();
    texture->SetTarget(target);

    const std::string path = this->_root + "/Textures/" + name + ".dds";

    IO::InputFile textureFile(path);
    if (!textureFile.IsOpen())
    {
        IO::Console::Instance().Error("Failed to open texture '%s'\n", name.c_str());
        return texture;
    }
    if (textureFile.IsEmpty())
    {
        IO::Console::Instance().Error("Failed to load texture '%s': Texture file is empty\n", name.c_str());
        textureFile.Close();
        return texture;
    }

    // Read texture into memory
    const size_t textureFileSize = textureFile.GetSize();
    std::vector<char> buffer(textureFileSize);
    textureFile.Read(buffer.data(), textureFileSize);

    textureFile.Close();

    // Load texture into GPU memory
    texture->Bind();
    DirectDrawSurfaceLoader::Instance().Load(texture, buffer);
    texture->Unbind();

    this->_textures.emplace(name, texture);

    return texture;
}

std::shared_ptr<Graphics::Font> Util::ResourcesLoader::LoadFont(const std::string& name)
{
    const auto it = this->_fonts.find(name);
    if (it != this->_fonts.end())
    {
        return it->second;
    }

    IO::Console::Instance().Info("Loading '%s' font\n", name.c_str());

    std::shared_ptr<Graphics::Font> font = std::make_shared<Graphics::Font>();
    std::shared_ptr<Graphics::Texture> fontMap = this->LoadTexture("Fonts/" + name);
    fontMap->Bind();
    fontMap->SetLODBias(0.0f);
    fontMap->Unbind();
    font->SetFontMap(fontMap);

    const std::string fontMappingPath = this->_root + "/Fonts/" + name + ".fnt";

    IO::InputFile fontMappingFile(fontMappingPath);
    if (!fontMappingFile.IsOpen())
    {
        IO::Console::Instance().Error("Failed to open font '%s'\n", name.c_str());
        return font;
    }
    if (fontMappingFile.IsEmpty())
    {
        IO::Console::Instance().Error("Failed to load model '%s': Model file is empty\n", name.c_str());
        fontMappingFile.Close();
        return font;
    }

    // Parse font mapping file
    const FontMappingLoader loader;
    loader.Load(font, fontMappingFile);

    fontMappingFile.Close();

    font->FinishLoading();

    return font;
}

std::shared_ptr<Graphics::Model> Util::ResourcesLoader::LoadModel(const std::string& name)
{
    const auto it = this->_models.find(name);
    if (it != this->_models.end())
    {
        return it->second;
    }

    IO::Console::Instance().Info("Loading '%s' model\n", name.c_str());

    std::shared_ptr<Graphics::Model> model = std::make_shared<Graphics::Model>();

    const std::string path = this->_root + "/Models/" + name + ".model";

    IO::InputFile modelFile(path);
    if (!modelFile.IsOpen())
    {
        IO::Console::Instance().Error("Failed to open model '%s'\n", name.c_str());
        return model;
    }
    if (modelFile.IsEmpty())
    {
        IO::Console::Instance().Error("Failed to load model '%s': Model file is empty\n", name.c_str());
        modelFile.Close();
        return model;
    }

    // Parse model file
    const ModelLoader loader;
    loader.Load(model, modelFile);

    modelFile.Close();

    model->FinishLoading();

    this->_models.emplace(name, model);

    return model;
}

void Util::ResourcesLoader::LoadScene(std::shared_ptr<Graphics::Scene>& scene, const std::string& name) const
{
    IO::Console::Instance().Info("Loading '%s' scene\n", name.c_str());

    const std::string path = this->_root + "/Scenes/" + name + ".yaml";

    IO::InputFile sceneFile(path);
    if (!sceneFile.IsOpen())
    {
        IO::Console::Instance().Error("Failed to open scene '%s'\n", name.c_str());
    }
    if (sceneFile.IsEmpty())
    {
        IO::Console::Instance().Error("Failed to load model '%s': Model file is empty\n", name.c_str());
        sceneFile.Close();
    }

    SceneLoader loader;
    loader.Load(scene, sceneFile);

    sceneFile.Close();
}

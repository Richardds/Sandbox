#include <fstream>
#include <string>
#include <gli/load_dds.hpp>

#include "ResourcesLoader.h"
#include "../IO/Console.h"
#include "Loaders/AssimpLoader.h"
#include "Loaders/DirectDrawSurfaceLoader.h"

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

	std::ifstream shaderFile(path, std::ios::binary | std::ios::ate);
	if (!shaderFile.is_open())
	{
		IO::Console::Instance().Error("Failed to open %s shader '%s'\n", type_str.c_str(), name.c_str());
		return shader;
	}

	const std::streamsize shaderFileSize = shaderFile.tellg();
	if (shaderFileSize == 0)
	{
		shaderFile.close();
		IO::Console::Instance().Error("Failed to load %s shader '%s'\n", type_str.c_str(), name.c_str());
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
	const auto it = this->_textures.find(name);
	if (it != this->_textures.end())
	{
		return it->second;
	}

	IO::Console::Instance().Info("Loading '%s' texture\n", name.c_str());

	std::shared_ptr<Graphics::Texture> texture = std::make_shared<Graphics::Texture>();
	texture->SetTarget(GL_TEXTURE_2D);

	const std::string path = this->_root + "/Textures/" + name + ".dds";

	std::ifstream textureFile(path, std::ios::binary | std::ios::ate);
	if (!textureFile.is_open())
	{
		IO::Console::Instance().Error("Failed to open texture '%s'\n", name.c_str());
		return texture;
	}

	const std::streamsize textureFileSize = textureFile.tellg();
	if (textureFileSize == 0)
	{
		IO::Console::Instance().Error("Failed to load texture '%s'\n", name.c_str());
		return texture;
	}
	textureFile.seekg(0, std::ios::beg);

	std::vector<char> buffer(textureFileSize);
	textureFile.read(buffer.data(), textureFileSize);
	textureFile.close();

	texture->Bind();
	DirectDrawSurfaceLoader::Instance().Load(texture, buffer);
	texture->Unbind();

	this->_textures.emplace(name, texture);

	return texture;
}

std::shared_ptr<Graphics::Texture> Util::ResourcesLoader::LoadCubeMap(const std::string& name) const
{
	IO::Console::Instance().Info("Loading '%s' cube map\n", name.c_str());

	std::shared_ptr<Graphics::Texture> cubeMap = std::make_shared<Graphics::Texture>();
	cubeMap->SetTarget(GL_TEXTURE_CUBE_MAP);

	const std::string path = this->_root + "/Textures/" + name + "_c.dds";

	std::ifstream cubeMapFile(path, std::ios::binary | std::ios::ate);
	if (!cubeMapFile.is_open())
	{
		IO::Console::Instance().Error("Failed to open '%s' cube map\n", name.c_str());
		return cubeMap;
	}

	const std::streamsize cubeMapPartFileSize = cubeMapFile.tellg();
	if (cubeMapPartFileSize == 0)
	{
		IO::Console::Instance().Error("Invalid file size of '%s' cube map\n", name.c_str());
		return cubeMap;
	}
	cubeMapFile.seekg(0, std::ios::beg);

	std::vector<char> buffer(cubeMapPartFileSize);
	cubeMapFile.read(buffer.data(), cubeMapPartFileSize);
	cubeMapFile.close();

	cubeMap->Bind();
	DirectDrawSurfaceLoader::Instance().Load(cubeMap, buffer);
	cubeMap->Unbind();

	return cubeMap;
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

	const std::string path = this->_root + "/Models/" + name + ".fbx";

	std::ifstream modelFile(path, std::ios::binary | std::ios::ate);
	if (!modelFile.is_open())
	{
		IO::Console::Instance().Error("Failed to open model '%s'\n", name.c_str());
		return model;
	}

	const std::streamsize modelFileSize = modelFile.tellg();
	if (modelFileSize == 0)
	{
		IO::Console::Instance().Error("Failed to load model '%s': Model file is empty\n", name.c_str());
		return model;
	}
	modelFile.seekg(0, std::ios::beg);

	std::vector<char> buffer(modelFileSize);
	modelFile.read(buffer.data(), modelFileSize);
	modelFile.close();

	AssimpLoader loader;

	try
	{
		model = loader.Load(buffer);
	}
	catch (const std::runtime_error& e)
	{
		IO::Console::Instance().Error("Failed to load model '%s': %s\n", name.c_str(), e.what());
		return model;
	}

	this->_models.emplace(name, model);

	return model;
}

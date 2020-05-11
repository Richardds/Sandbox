#include <gli/load_dds.hpp>

#include "DirectDrawSurfaceLoader.h"

Util::DirectDrawSurfaceLoader::DirectDrawSurfaceLoader()
{
}

Util::DirectDrawSurfaceLoader::~DirectDrawSurfaceLoader()
{
}

std::shared_ptr<Graphics::Texture> Util::DirectDrawSurfaceLoader::Load(const std::vector<char>& buffer)
{
	std::shared_ptr<Graphics::Texture> texture = std::make_shared<Graphics::Texture>(GL_TEXTURE_2D);

	gli::texture textureData = gli::load_dds(buffer.data(), buffer.size());
	
	texture->Bind();
	texture->Data(textureData);
	texture->Unbind();

	return texture;
}

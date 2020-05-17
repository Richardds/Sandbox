#include <gli/load_dds.hpp>

#include "DirectDrawSurfaceLoader.h"

std::shared_ptr<Graphics::Texture> Util::DirectDrawSurfaceLoader::Load(const std::vector<char>& buffer) const
{
	std::shared_ptr<Graphics::Texture> texture = std::make_shared<Graphics::Texture>(GL_TEXTURE_2D);

	const gli::texture textureData = gli::load_dds(buffer.data(), buffer.size());

	texture->Bind();
	texture->Data(textureData);
	texture->Unbind();

	return texture;
}

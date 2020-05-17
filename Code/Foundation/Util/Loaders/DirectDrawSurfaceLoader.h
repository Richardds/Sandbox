#pragma once

#include <vector>

#include "../../Graphics/Texture.h"

namespace Util
{
	class DirectDrawSurfaceLoader
	{
	public:
		DirectDrawSurfaceLoader() = default;
		std::shared_ptr<Graphics::Texture> Load(const std::vector<char>& buffer) const;
	};
}

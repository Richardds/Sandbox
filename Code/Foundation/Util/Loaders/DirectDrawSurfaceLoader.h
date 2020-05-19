#pragma once

#include <vector>
#include <gli/gl.hpp>

#include "../../Core/Singleton.h"
#include "../../Graphics/Texture.h"

namespace Util
{
	class DirectDrawSurfaceLoader
	{
		_Singleton(DirectDrawSurfaceLoader)
		
	public:
		struct TextureInfo
		{
			GLenum target;
		};
		
		DirectDrawSurfaceLoader() = default;
		void Load(std::shared_ptr<Graphics::Texture>& texture, std::vector<char>& buffer) const;

	private:
		void Load1dTexture(std::shared_ptr<Graphics::Texture>& texture, const gli::texture& gliTexture, const gli::gl::format& gliFormat) const;
		void Load2dTexture(std::shared_ptr<Graphics::Texture>& texture, const gli::texture& gliTexture, const gli::gl::format& gliFormat) const;
		void LoadCubeTexture(std::shared_ptr<Graphics::Texture>& texture, const gli::texture& gliTexture, const gli::gl::format& gliFormat) const;
		void Load3dTexture(std::shared_ptr<Graphics::Texture>& texture, const gli::texture& gliTexture, const gli::gl::format& gliFormat) const;
	};
}

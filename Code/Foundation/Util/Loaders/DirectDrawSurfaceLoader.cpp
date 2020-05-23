// ----------------------------------------------------------------------------------------
//  \file       DirectDrawSurfaceLoader.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Util/Loaders/DirectDrawSurfaceLoader.h"
#include "IO/Console.h"

void Util::DirectDrawSurfaceLoader::Load(std::shared_ptr<Graphics::Texture>& texture, std::vector<char>& buffer) const
{
	_Assert(texture->IsBound());

	const gli::texture gliTexture = gli::load_dds(buffer.data(), buffer.size());

	_Assert(!gliTexture.empty());

	const gli::gl gl(gli::gl::PROFILE_GL33);
	const GLenum target = gl.translate(gliTexture.target());

	_Assert(texture->GetTarget() == target);

	const gli::gl::format gliFormat = gl.translate(gliTexture.format(), gliTexture.swizzles());
	const glm::tvec3<GLsizei> dimensions(gliTexture.extent());

	texture->SetWidth(dimensions.x);
	texture->SetHeight(dimensions.y);
	texture->SetDepth(dimensions.z);

	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(gliTexture.levels() - 1));
	glTexParameteri(target, GL_TEXTURE_SWIZZLE_R, gliFormat.Swizzles[0]);
	glTexParameteri(target, GL_TEXTURE_SWIZZLE_G, gliFormat.Swizzles[1]);
	glTexParameteri(target, GL_TEXTURE_SWIZZLE_B, gliFormat.Swizzles[2]);
	glTexParameteri(target, GL_TEXTURE_SWIZZLE_A, gliFormat.Swizzles[3]);

	switch (gliTexture.target())
	{
	case gli::TARGET_1D:
		this->Load1dTexture(texture, gliTexture, gliFormat);
		break;
	case gli::TARGET_2D:
		this->Load2dTexture(texture, gliTexture, gliFormat);
		break;
	case gli::TARGET_CUBE:
		this->LoadCubeTexture(texture, gliTexture, gliFormat);
		break;
	case gli::TARGET_3D:
		this->Load3dTexture(texture, gliTexture, gliFormat);
		break;
	default:
		IO::Console::Instance().Error("Unsupported texture target\n");
	}

	texture->FinishLoading();
}

void Util::DirectDrawSurfaceLoader::Load1dTexture(std::shared_ptr<Graphics::Texture>& texture,
                                                  const gli::texture& gliTexture,
                                                  const gli::gl::format& gliFormat) const
{
	glTexParameteri(texture->GetTarget(), GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexStorage1D(
		texture->GetTarget(),
		static_cast<GLint>(gliTexture.levels()),
		gliFormat.Internal,
		static_cast<GLsizei>(texture->GetWidth())
	);

	for (size_t layer = 0; layer < gliTexture.layers(); ++layer)
	{
		for (size_t face = 0; face < gliTexture.faces(); ++face)
		{
			for (size_t level = 0; level < gliTexture.levels(); ++level)
			{
				const glm::tvec3<GLsizei> dimensions(gliTexture.extent(level));

				if (gli::is_compressed(gliTexture.format()))
				{
					glCompressedTexSubImage1D(
						texture->GetTarget(),
						static_cast<GLint>(level),
						0,
						dimensions.x,
						gliFormat.Internal,
						static_cast<GLsizei>(gliTexture.size(level)),
						gliTexture.data(layer, face, level)
					);
				}
				else
				{
					glTexSubImage1D(
						texture->GetTarget(),
						static_cast<GLint>(level),
						0,
						dimensions.x,
						gliFormat.External,
						gliFormat.Type,
						gliTexture.data(layer, face, level)
					);
				}
			}
		}
	}
}

void Util::DirectDrawSurfaceLoader::Load2dTexture(std::shared_ptr<Graphics::Texture>& texture,
                                                  const gli::texture& gliTexture,
                                                  const gli::gl::format& gliFormat) const
{
	const GLenum target = texture->GetTarget();

	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexStorage2D(
		target,
		static_cast<GLint>(gliTexture.levels()),
		gliFormat.Internal,
		texture->GetWidth(),
		texture->GetHeight()
	);

	for (size_t layer = 0; layer < gliTexture.layers(); ++layer)
	{
		for (size_t face = 0; face < gliTexture.faces(); ++face)
		{
			for (size_t level = 0; level < gliTexture.levels(); ++level)
			{
				const glm::tvec3<GLsizei> dimensions(gliTexture.extent(level));

				if (gli::is_compressed(gliTexture.format()))
				{
					glCompressedTexSubImage2D(
						target,
						static_cast<GLint>(level),
						0,
						0,
						dimensions.x,
						dimensions.y,
						gliFormat.Internal,
						static_cast<GLsizei>(gliTexture.size(level)),
						gliTexture.data(layer, face, level)
					);
				}
				else
				{
					glTexSubImage2D(
						target,
						static_cast<GLint>(level),
						0,
						0,
						dimensions.x,
						dimensions.y,
						gliFormat.External,
						gliFormat.Type,
						gliTexture.data(layer, face, level)
					);
				}
			}
		}
	}
}

void Util::DirectDrawSurfaceLoader::LoadCubeTexture(std::shared_ptr<Graphics::Texture>& texture,
                                                    const gli::texture& gliTexture,
                                                    const gli::gl::format& gliFormat) const
{
	GLenum target = texture->GetTarget();

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glTexStorage2D(
		target,
		static_cast<GLint>(gliTexture.levels()),
		gliFormat.Internal,
		texture->GetWidth(),
		texture->GetHeight()
	);

	for (size_t layer = 0; layer < gliTexture.layers(); ++layer)
	{
		for (size_t face = 0; face < gliTexture.faces(); ++face)
		{
			for (size_t level = 0; level < gliTexture.levels(); ++level)
			{
				const glm::tvec3<GLsizei> dimensions(gliTexture.extent(level));

				target = static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face);

				if (gli::is_compressed(gliTexture.format()))
				{
					glCompressedTexSubImage2D(
						target,
						static_cast<GLint>(level),
						0,
						0,
						dimensions.x,
						dimensions.y,
						gliFormat.Internal,
						static_cast<GLsizei>(gliTexture.size(level)),
						gliTexture.data(layer, face, level)
					);
				}
				else
				{
					glTexSubImage2D(
						target,
						static_cast<GLint>(level),
						0,
						0,
						dimensions.x,
						dimensions.y,
						gliFormat.External,
						gliFormat.Type,
						gliTexture.data(layer, face, level)
					);
				}
			}
		}
	}
}

void Util::DirectDrawSurfaceLoader::Load3dTexture(std::shared_ptr<Graphics::Texture>& texture,
                                                  const gli::texture& gliTexture,
                                                  const gli::gl::format& gliFormat) const
{
	const GLenum target = texture->GetTarget();

	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_REPEAT);

	glTexStorage3D(
		target,
		static_cast<GLint>(gliTexture.levels()),
		gliFormat.Internal,
		texture->GetWidth(),
		texture->GetHeight(),
		texture->GetDepth()
	);

	for (size_t layer = 0; layer < gliTexture.layers(); ++layer)
	{
		for (size_t face = 0; face < gliTexture.faces(); ++face)
		{
			for (size_t level = 0; level < gliTexture.levels(); ++level)
			{
				const glm::tvec3<GLsizei> dimensions(gliTexture.extent(level));

				if (gli::is_compressed(gliTexture.format()))
				{
					glCompressedTexSubImage3D(
						target,
						static_cast<GLint>(level),
						0,
						0,
						0,
						dimensions.x,
						dimensions.y,
						dimensions.z,
						gliFormat.Internal,
						static_cast<GLsizei>(gliTexture.size(level)),
						gliTexture.data(layer, face, level)
					);
				}
				else
				{
					glTexSubImage3D(
						target,
						static_cast<GLint>(level),
						0,
						0,
						0,
						dimensions.x,
						dimensions.y,
						dimensions.z,
						gliFormat.External,
						gliFormat.Type,
						gliTexture.data(layer, face, level)
					);
				}
			}
		}
	}
}

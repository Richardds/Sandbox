// ----------------------------------------------------------------------------------------
//  \file       DirectDrawSurfaceLoader.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Singleton.h"
#include "Graphics/Texture.h"

namespace Util
{
    /// Direct draw surface texture loader which uses GLI library
    class EXPORT DirectDrawSurfaceLoader
    {
    _Singleton(DirectDrawSurfaceLoader)

    public:
        DirectDrawSurfaceLoader() = default;
        virtual ~DirectDrawSurfaceLoader() = default;

        void Load(std::shared_ptr<Graphics::Texture>& texture, std::vector<char>& buffer) const;

    private:
        void Load1dTexture(std::shared_ptr<Graphics::Texture>& texture,
                           const gli::texture& gliTexture,
                           const gli::gl::format& gliFormat) const;
        void Load2dTexture(std::shared_ptr<Graphics::Texture>& texture,
                           const gli::texture& gliTexture,
                           const gli::gl::format& gliFormat) const;
        void LoadCubeTexture(std::shared_ptr<Graphics::Texture>& texture,
                             const gli::texture& gliTexture,
                             const gli::gl::format& gliFormat) const;
        void Load3dTexture(std::shared_ptr<Graphics::Texture>& texture,
                           const gli::texture& gliTexture,
                           const gli::gl::format& gliFormat) const;
    };
}

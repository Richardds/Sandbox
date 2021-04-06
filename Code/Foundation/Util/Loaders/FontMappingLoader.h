// ----------------------------------------------------------------------------------------
//  \file       FontMappingLoader.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/Font.h"

namespace Util
{
    /// Loader to fill font characters mapping
    class FontMappingLoader
    {
    public:
        FontMappingLoader() = default;
        virtual ~FontMappingLoader() = default;

        void Load(std::shared_ptr<Graphics::Font>& font, std::ifstream& fontMappingFile) const;

    private:
        static const char* CharacterMappingRegex;
    };
}

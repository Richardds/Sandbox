// ----------------------------------------------------------------------------------------
//  \file       FontType.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Texture.h"

namespace Graphics
{
    class FontType
    {
    public:
        enum class State
        {
            Initial,
            Loaded
        };

        [[nodiscard]] std::shared_ptr<Texture> GetGlyphsMap() const;
        void SetGlyphsMap(const std::shared_ptr<Texture>& texture);

    private:
        std::shared_ptr<Texture> _glyphsMap;
    };

    inline std::shared_ptr<Texture> FontType::GetGlyphsMap() const
    {
        return this->_glyphsMap;
    }

    inline void FontType::SetGlyphsMap(const std::shared_ptr<Texture>& texture)
    {
        _Assert(texture);
        _Assert(Texture::State::Loaded == texture->GetState());
        this->_glyphsMap = texture;
    }
}

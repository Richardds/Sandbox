// ----------------------------------------------------------------------------------------
//  \file       Font.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Texture.h"

namespace Graphics
{
    class Font
    {
    public:
        struct CharacterMapping
        {
            float width;
            float height;
            Math::Vector2f offset;
        };

        Font(const std::shared_ptr<Texture>& fontMap,
                 const std::unordered_map<char, CharacterMapping>& charactersMapping);
        virtual ~Font() = default;

        [[nodiscard]] CharacterMapping GetCharacterMapping(char character) const;
        [[nodiscard]] std::shared_ptr<Texture> GetFontMap() const;
        void SetFontMap(const std::shared_ptr<Texture>& texture);

    private:
        std::shared_ptr<Texture> _fontMap;
        std::unordered_map<char, CharacterMapping> _charactersMapping;
    };

    inline std::shared_ptr<Texture> Font::GetFontMap() const
    {
        return this->_fontMap;
    }

    inline void Font::SetFontMap(const std::shared_ptr<Texture>& texture)
    {
        this->_fontMap = texture;
    }
}

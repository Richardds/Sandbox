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
        struct CharacterProperties
        {
            struct Mapping
            {
                Math::Vector2f offset;
                float width;
                float height;
            } mapping;
            struct Positioning
            {
                Math::Vector2f offset;
                float advance;
            } positioning;
        };

        Font(const std::shared_ptr<Texture>& fontMap,
                 const std::unordered_map<char, CharacterProperties>& charactersMapping);
        virtual ~Font() = default;

        [[nodiscard]] CharacterProperties GetCharacterMapping(char character) const;
        [[nodiscard]] std::shared_ptr<Texture> GetFontMap() const;
        void SetFontMap(const std::shared_ptr<Texture>& texture);

    private:
        std::shared_ptr<Texture> _fontMap;
        std::unordered_map<char, CharacterProperties> _charactersMapping;
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

// ----------------------------------------------------------------------------------------
//  \file       TextType.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Texture.h"

namespace Graphics
{
    class TextType
    {
    public:
        struct CharacterMapping
        {
            float width;
            float height;
            Math::Vector2f offset;
        };

        TextType(const std::shared_ptr<Texture>& fontMap,
                 const std::unordered_map<char, CharacterMapping>& charactersMapping);
        virtual ~TextType() = default;

        const CharacterMapping& GetCharacterMapping(char character);
        [[nodiscard]] std::shared_ptr<Texture> GetFontMap() const;
        void SetFontMap(const std::shared_ptr<Texture>& texture);

    private:
        std::shared_ptr<Texture> _fontMap;
        std::unordered_map<char, CharacterMapping> _charactersMapping;
    };

    inline std::shared_ptr<Texture> TextType::GetFontMap() const
    {
        return this->_fontMap;
    }

    inline void TextType::SetFontMap(const std::shared_ptr<Texture>& texture)
    {
        this->_fontMap = texture;
    }
}

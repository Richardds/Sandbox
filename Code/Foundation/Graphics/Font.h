// ----------------------------------------------------------------------------------------
//  \file       Font.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Types.h"
#include "Texture.h"

namespace Graphics
{
    class Font
    {
    public:
        enum class State
        {
            Initial,
            Loaded
        };

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

        Font();
        virtual ~Font() = default;

        [[nodiscard]] State GetState() const;
        [[nodiscard]] std::shared_ptr<Texture> GetFontMap() const;
        void SetFontMap(const std::shared_ptr<Texture>& fontMap);

        void AddCharacterProperties(Character character, const CharacterProperties& props);
        [[nodiscard]] CharacterProperties GetCharacterProperties(Character character) const;
        [[nodiscard]] bool Empty() const;
        [[nodiscard]] std::unordered_map<Character, CharacterProperties> GetCharactersProperties() const;
        void FinishLoading();

    private:
        State _state;
        std::shared_ptr<Texture> _fontMap;
        std::unordered_map<Character, CharacterProperties> _charactersProperties;
    };

    inline Font::State Font::GetState() const
    {
        return this->_state;
    }

    inline std::shared_ptr<Texture> Font::GetFontMap() const
    {
        return this->_fontMap;
    }

    inline void Font::SetFontMap(const std::shared_ptr<Texture>& fontMap)
    {
        _Assert(fontMap->GetState() == Texture::State::Loaded);
        this->_fontMap = fontMap;
    }

    inline bool Font::Empty() const
    {
        return !this->_charactersProperties.empty();
    }

    inline std::unordered_map<Character, Font::CharacterProperties> Font::GetCharactersProperties() const
    {
        return this->_charactersProperties;
    }

    inline void Font::FinishLoading()
    {
        _Assert(State::Initial == this->_state);

        this->_state = State::Loaded;
    }
}

// ----------------------------------------------------------------------------------------
//  \file       Font.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Types.h"
#include "Texture.h"

namespace Graphics
{
    class EXPORT Font
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

        State GetState() const;
        std::shared_ptr<Texture> GetFontMap() const;
        void SetFontMap(const std::shared_ptr<Texture>& fontMap);
        void SetConfig(float size, float spacing, bool isBold, bool isItalic);
        float GetSize() const;
        float GetSpacing() const;
        bool IsBold() const;
        bool IsItalic() const;
        void AddCharacterProperties(Character character, const CharacterProperties& props);
        CharacterProperties GetCharacterProperties(Character character) const;
        void FinishLoading();

    private:
        State _state;
        std::shared_ptr<Texture> _fontMap;
        std::unordered_map<Character, CharacterProperties> _charactersProperties;
        float _size;
        float _spacing;
        bool _isBold;
        bool _isItalic;
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
        _Assert(State::Initial == this->_state)
        _Assert(Texture::State::Loaded == fontMap->GetState())

        this->_fontMap = fontMap;
    }

    inline void Font::SetConfig(const float size, const float spacing, const bool isBold, const bool isItalic)
    {
        _Assert(State::Initial == this->_state)
        _Assert(0.0f < size)

        this->_size = size;
        this->_spacing = spacing;
        this->_isBold = isBold;
        this->_isItalic = isItalic;
    }

    inline float Font::GetSize() const
    {
        return this->_size;
    }

    inline float Font::GetSpacing() const
    {
        return this->_spacing;
    }

    inline bool Font::IsBold() const
    {
        return this->_isBold;
    }

    inline bool Font::IsItalic() const
    {
        return this->_isItalic;
    }

    inline void Font::FinishLoading()
    {
        _Assert(State::Initial == this->_state)

        this->_state = State::Loaded;
    }
}

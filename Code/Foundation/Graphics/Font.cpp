// ----------------------------------------------------------------------------------------
//  \file       Font.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Font.h"

Graphics::Font::Font() :
    _state(State::Initial),
    _size(50.0f),
    _spacing(8.0f),
    _isBold(false),
    _isItalic(false)
{
}

void Graphics::Font::AddCharacterProperties(const Character character, const CharacterProperties& props)
{
    _Assert(State::Initial == this->_state)

    this->_charactersProperties[character] = props;
}

Graphics::Font::CharacterProperties Graphics::Font::GetCharacterProperties(const Character character) const
{
    _Assert(State::Loaded == this->_state)

    // Search for character in mapping hash table
    auto it = this->_charactersProperties.find(character);

    // Return character properties when found
    if (it != this->_charactersProperties.end())
    {
        return it->second;
    }

    // Search for hashtag character whe not found
    it = this->_charactersProperties.find('#');
    if (it != this->_charactersProperties.end())
    {
        return it->second;
    }

    // Else return empty mapping (no character will be rendered)
    return {};
}

// ----------------------------------------------------------------------------------------
//  \file       Font.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Font.h"

Graphics::Font::Font() :
    _state(State::Initial)
{
}

void Graphics::Font::AddCharacterProperties(const Character character, const CharacterProperties& props)
{
    this->_charactersProperties[character] = props;
}

Graphics::Font::CharacterProperties Graphics::Font::GetCharacterProperties(const Character character) const
{
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

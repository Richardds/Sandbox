// ----------------------------------------------------------------------------------------
//  \file       TextType.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/TextType.h"

Graphics::TextType::TextType(const std::shared_ptr<Texture>& fontMap,
                             const std::unordered_map<char, CharacterMapping>& charactersMapping) :
    _fontMap(fontMap),
    _charactersMapping(charactersMapping)
{
    // Make sure the font texture is already loaded
    _Assert(fontMap->GetState() == Texture::State::Loaded);
    // Make sure the font texture is square
    _Assert(fontMap->GetWidth() == fontMap->GetHeight());
    // Make sure the characters mapping is not empty
    _Assert(!charactersMapping.empty());
}

const Graphics::TextType::CharacterMapping& Graphics::TextType::GetCharacterMapping(const char character)
{
    const auto it = this->_charactersMapping.find(character);
    if (it != this->_charactersMapping.end())
    {
        return it->second;
    }

    return {};
}

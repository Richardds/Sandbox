// ----------------------------------------------------------------------------------------
//  \file       FontMappingLoader.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Util/Loaders/FontMappingLoader.h"
#include "Core/Types.h"

const char* Util::FontMappingLoader::CharacterMappingRegex = "^char +id=([0-9]+)"
                                                             " +x=([0-9]+) +y=([0-9]+)"
                                                             " +width=([0-9]+) +height=([0-9]+)"
                                                             " +xoffset=(-?[0-9]+) +yoffset=(-?[0-9]+) +xadvance=([0-9]+)"
                                                             " +page=([0-9]+) +chnl=([0-9]+) +$";

void Util::FontMappingLoader::Load(std::shared_ptr<Graphics::Font>& font, std::ifstream& fontMappingFile) const
{
    std::string line;
    std::smatch match;
    bool enteredCharSection = false;

    const std::regex regex(CharacterMappingRegex);

    while (fontMappingFile.good())
    {
        std::getline(fontMappingFile, line);

        if (std::regex_match(line, match, regex)) {
            enteredCharSection = true;

            Character character = static_cast<Character>(std::stoi(match[1]));
            Graphics::Font::CharacterProperties props = {
                Math::Vector2f(static_cast<float>(std::stoi(match[2])), static_cast<float>(std::stoi(match[3]))),
                static_cast<float>(std::stoi(match[4])), static_cast<float>(std::stoi(match[5])),
                Math::Vector2f(static_cast<float>(std::stoi(match[6])), static_cast<float>(std::stoi(match[7]))),
                static_cast<float>(std::stoi(match[8]))
            };

            font->AddCharacterProperties(character, props);
        } else
        {
            // Finish parsing when at the end of "char" section
            if (enteredCharSection)
            {
                break;
            }
        }
    }
}

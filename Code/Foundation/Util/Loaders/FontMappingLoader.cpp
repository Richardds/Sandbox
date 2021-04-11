// ----------------------------------------------------------------------------------------
//  \file       FontMappingLoader.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Util/Loaders/FontMappingLoader.h"
#include "Core/Types.h"
#include "Core/Exception/ParsingException.h"

const char* Util::FontMappingLoader::FontInfoHeaderRegex = "^info face=\"([a-zA-Z0-9]*)\" size=([0-9]+)"
                                                           " bold=([01]) italic=([01]) charset=\"([a-zA-Z0-9]*)\""
                                                           " unicode=([01]) stretchH=([0-9]+) smooth=([01]) aa=([01])"
                                                           " padding=(-?[0-9]+),(-?[0-9]+),(-?[0-9]+),(-?[0-9]+)"
                                                           " spacing=(-?[0-9]+),(-?[0-9]+) *$";

const char* Util::FontMappingLoader::CharacterMappingRegex = "^char +id=([0-9]+)"
                                                             " +x=([0-9]+) +y=([0-9]+)"
                                                             " +width=([0-9]+) +height=([0-9]+)"
                                                             " +xoffset=(-?[0-9]+) +yoffset=(-?[0-9]+) +xadvance=([0-9]+)"
                                                             " +page=([0-9]+) +chnl=([0-9]+) *$";

void Util::FontMappingLoader::Load(std::shared_ptr<Graphics::Font>& font, IO::InputFile& fontMappingFile) const
{
    std::string line;
    std::smatch match;
    bool enteredCharSection = false;

    const std::regex regex(CharacterMappingRegex);

    // Parse info header
    fontMappingFile.ReadLine(line);
    if (!std::regex_match(line, match, std::regex(FontInfoHeaderRegex))) {
        throw Core::ParsingException("Invalid info header");
    }
    
    font->SetConfig(
        // Texture font size
        static_cast<float>(std::stoi(match[2])),
        // Unwanted offset added by signed distance field effect
        (static_cast<float>(std::stoi(match[13])) + static_cast<float>(std::stoi(match[11]))) / 2.0f,
        // Font type bold
        std::stoi(match[3]) == 1,
        // Font type italic
        std::stoi(match[4]) == 1
    );

    while (!fontMappingFile.IsEndOfFile())
    {
        fontMappingFile.ReadLine(line);

        if (std::regex_match(line, match, regex)) {
            enteredCharSection = true;

            Character character = static_cast<Character>(std::stoi(match[1]));
            Graphics::Font::CharacterProperties props = {
                {
                    Math::Vector2f(static_cast<float>(std::stoi(match[2])), static_cast<float>(std::stoi(match[3]))),
                static_cast<float>(std::stoi(match[4])), static_cast<float>(std::stoi(match[5]))
                },
                {
                    Math::Vector2f(static_cast<float>(std::stoi(match[6])), static_cast<float>(std::stoi(match[7]))),
                static_cast<float>(std::stoi(match[8]))
                }
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

// ----------------------------------------------------------------------------------------
//  \file       ParsingException.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Core/Exception/ParsingException.h"

Core::ParsingException::ParsingException(const std::string& message) :
    Exception(message)
{
}

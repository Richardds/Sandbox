// ----------------------------------------------------------------------------------------
//  \file       ParsingException.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Core/Exception/UnsupportedException.h"

Core::UnsupportedException::UnsupportedException(const std::string& message) :
    Exception(message)
{
}

// ----------------------------------------------------------------------------------------
//  \file       ParsingException.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Core/Exception/UnsupportedException.h"

Core::UnsupportedException::UnsupportedException(const std::string& message) :
    Exception(message)
{
}

// ----------------------------------------------------------------------------------------
//  \file       IOException.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Core/Exception/IOException.h"

Core::IOException::IOException(const std::string& message) :
    Exception(message)
{
}

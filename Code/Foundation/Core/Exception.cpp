// ----------------------------------------------------------------------------------------
//  \file       Exception.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Core/Exception.h"

Core::Exception::Exception(const std::string& message) :
    _message(message)
{
}

const char* Core::Exception::what() const
{
    return this->_message.c_str();
}

// ----------------------------------------------------------------------------------------
//  \file       String.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Util/String.h"

std::string Util::String::Format(const char* format, ...)
{
    char buffer[1024];

    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    return buffer;
}

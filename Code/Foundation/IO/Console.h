// ----------------------------------------------------------------------------------------
//  \file       Console.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Singleton.h"

namespace IO
{
    /// Helper class for writing text to a console
    class Console
    {
    _Singleton(Console)

    public:
        Console() = default;
        void __cdecl Write(FILE* handle, const char* format, ...);
        void __cdecl Info(const char* format, ...);
        void __cdecl Warning(const char* format, ...);
        void __cdecl Error(const char* format, ...);
    };
}

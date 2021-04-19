// ----------------------------------------------------------------------------------------
//  \file       Console.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Core/Singleton.h"

namespace IO
{
    /// Helper class for writing text to a console
    class EXPORT Console
    {
    _Singleton(Console)

    public:
        Console() = default;
        virtual ~Console() = default;

        void __cdecl Write(FILE* handle, const char* format, ...);
        void __cdecl Info(const char* format, ...);
        void __cdecl Warning(const char* format, ...);
        void __cdecl Error(const char* format, ...);
    };
}

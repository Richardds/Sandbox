// ----------------------------------------------------------------------------------------
//  \file       String.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"

namespace Util
{
    /// std::string utilities
    class EXPORT String final
    {
    public:
        static std::string __cdecl Format(const char* format, ...);
    };
}

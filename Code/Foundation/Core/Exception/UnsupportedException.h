// ----------------------------------------------------------------------------------------
//  \file       UnsupportedException.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Exception.h"

namespace Core
{
    /// Exception class for all IO operations
    class EXPORT UnsupportedException : public Exception
    {
    public:
        UnsupportedException(const std::string& message);
    };
}

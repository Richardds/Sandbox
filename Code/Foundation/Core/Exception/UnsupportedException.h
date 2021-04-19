// ----------------------------------------------------------------------------------------
//  \file       UnsupportedException.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
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

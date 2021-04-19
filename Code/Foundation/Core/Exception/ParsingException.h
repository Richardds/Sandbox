// ----------------------------------------------------------------------------------------
//  \file       ParsingException.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Core/Exception.h"

namespace Core
{
    /// Exception class for all IO operations
    class EXPORT ParsingException : public Exception
    {
    public:
        ParsingException(const std::string& message);
    };
}

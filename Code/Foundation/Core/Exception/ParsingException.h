// ----------------------------------------------------------------------------------------
//  \file       ParsingException.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Exception.h"

namespace Core
{
    /// Exception class for all IO operations
    class EXPORT ParsingException : public Exception
    {
    public:
        ParsingException(const std::string& message);
        virtual ~ParsingException() = default;
    };
}

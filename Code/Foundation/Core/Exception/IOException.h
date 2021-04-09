// ----------------------------------------------------------------------------------------
//  \file       IOException.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Exception.h"

namespace Core
{
    /// Exception class for all IO operations
    class EXPORT IOException : public Exception
    {
    public:
        IOException(const std::string& message);
        virtual ~IOException() = default;
    };
}

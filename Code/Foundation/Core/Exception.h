// ----------------------------------------------------------------------------------------
//  \file       Exception.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"

namespace Core
{
    /// Base class of all Sandbox exceptions
    class EXPORT Exception : public std::exception
    {
    public:
        explicit Exception(const std::string& message);

        std::string GetMessage() const;
        const char* what() const override;

    private:
        std::string _message;
    };

    inline std::string Exception::GetMessage() const
    {
        return this->_message;
    }

}

// ----------------------------------------------------------------------------------------
//  \file       Exception.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"

namespace Core
{
    /// Base class of all Sandbox exceptions
    class EXPORT Exception : public std::exception
    {
    public:
        explicit Exception(const std::string& message);

        std::string GetMessage() const;
        const char* what() const throw() override;

    private:
        std::string _message;
    };

    inline std::string Exception::GetMessage() const
    {
        return this->_message;
    }

}

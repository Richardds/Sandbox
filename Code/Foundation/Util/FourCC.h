// ----------------------------------------------------------------------------------------
//  \file       FourCC.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"

namespace Util
{
    /// Magic 4 byte identifier class
    class EXPORT FourCC final
    {
    public:
        static std::string ToString(const FourCC& fourCC);
        static FourCC FromString(const std::string& fourCC);

        FourCC();
        FourCC(uint32_t fourCC);
        FourCC(const std::string& fourCC);

        bool operator==(const FourCC& rhs) const;
        bool operator!=(const FourCC& rhs) const;
        bool operator<(const FourCC& rhs) const;
        bool operator<=(const FourCC& rhs) const;
        bool operator>(const FourCC& rhs) const;
        bool operator>=(const FourCC& rhs) const;
        bool IsValid() const;
        void SetFromUint32(uint32_t fourCC);
        uint32_t ToUint32() const;
        void SetFromString(const std::string& fourCC);
        std::string ToString() const;

    private:
        uint32_t _fourCC;
    };
}

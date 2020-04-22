#pragma once

#include <string>

#include "../Core/Debug.h"

namespace Util
{

    class FourCC
    {
    public:
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
        uint32_t toUint32() const;
        void SetFromString(const std::string& fourCC);
        std::string toString() const;
        static std::string ToString(const FourCC& fourCC);
        static FourCC FromString(const std::string& fourCC);

    private:
        uint32_t _fourCC;
    };

}

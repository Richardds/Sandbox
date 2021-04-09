// ----------------------------------------------------------------------------------------
//  \file       FourCC.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Util/FourCC.h"
#include "Core/Debug.h"

std::string Util::FourCC::ToString(const FourCC& fourCC)
{
    _Assert(fourCC.IsValid())

    std::string str("AAAA");
    str[0] = static_cast<char>((fourCC._fourCC & 0xFF000000) >> 24);
    str[1] = static_cast<char>((fourCC._fourCC & 0x00FF0000) >> 16);
    str[2] = static_cast<char>((fourCC._fourCC & 0x0000FF00) >> 8);
    str[3] = static_cast<char>(fourCC._fourCC & 0x000000FF);

    return str;
}

Util::FourCC Util::FourCC::FromString(const std::string& fourCC)
{
    _Assert(4 == fourCC.length())

    return FourCC(static_cast<uint32_t>(fourCC[0] | fourCC[1] << 8 | fourCC[2] << 16 | fourCC[3] << 24));
}

Util::FourCC::FourCC() :
    _fourCC(0)
{
}

Util::FourCC::FourCC(const uint32_t fourCC) :
    _fourCC(fourCC)
{
}

Util::FourCC::FourCC(const std::string& fourCC) :
    _fourCC(0)
{
    this->SetFromString(fourCC);
}

bool Util::FourCC::operator==(const FourCC& rhs) const
{
    return this->_fourCC == rhs._fourCC;
}

bool Util::FourCC::operator!=(const FourCC& rhs) const
{
    return this->_fourCC != rhs._fourCC;
}

bool Util::FourCC::operator<(const FourCC& rhs) const
{
    return this->_fourCC < rhs._fourCC;
}

bool Util::FourCC::operator<=(const FourCC& rhs) const
{
    return this->_fourCC <= rhs._fourCC;
}

bool Util::FourCC::operator>(const FourCC& rhs) const
{
    return this->_fourCC > rhs._fourCC;
}

bool Util::FourCC::operator>=(const FourCC& rhs) const
{
    return this->_fourCC >= rhs._fourCC;
}

bool Util::FourCC::IsValid() const
{
    return (0 != this->_fourCC);
}

void Util::FourCC::SetFromUint32(const uint32_t fourCC)
{
    _Assert(0 != fourCC)
    this->_fourCC = fourCC;
}

uint32_t Util::FourCC::ToUint32() const
{
    return this->_fourCC;
}

void Util::FourCC::SetFromString(const std::string& fourCC)
{
    *this = FromString(fourCC);
}

std::string Util::FourCC::ToString() const
{
    return ToString(*this);
}

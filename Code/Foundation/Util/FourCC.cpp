#include "FourCC.h"

Util::FourCC::FourCC() :
    _fourCC(0)
{
}

Util::FourCC::FourCC(uint32_t fourCC) :
    _fourCC(fourCC)
{
}

Util::FourCC::FourCC(const std::string& fourCC)
{
    this->SetFromString(fourCC);
}

bool Util::FourCC::operator==(const FourCC& rhs) const
{
    return (this->_fourCC == rhs._fourCC);
}

bool Util::FourCC::operator!=(const FourCC& rhs) const
{
    return (this->_fourCC != rhs._fourCC);
}

bool Util::FourCC::operator<(const FourCC& rhs) const
{
    return (this->_fourCC < rhs._fourCC);
}

bool Util::FourCC::operator<=(const FourCC& rhs) const
{
    return (this->_fourCC <= rhs._fourCC);
}

bool Util::FourCC::operator>(const FourCC& rhs) const
{
    return (this->_fourCC > rhs._fourCC);
}

bool Util::FourCC::operator>=(const FourCC& rhs) const
{
    return (this->_fourCC >= rhs._fourCC);
}

bool Util::FourCC::IsValid() const
{
    return (0 != this->_fourCC);
}

void Util::FourCC::SetFromUint32(uint32_t fourCC)
{
    _assert(0 != fourCC);
    this->_fourCC = fourCC;
}

uint32_t Util::FourCC::toUint32() const
{
    return this->_fourCC;
}

void Util::FourCC::SetFromString(const std::string& fourCC)
{
    *this = this->FromString(fourCC);
}

std::string Util::FourCC::toString() const
{
    return this->ToString(*this);
}

std::string Util::FourCC::ToString(const FourCC& fourCC)
{
    _assert(fourCC.IsValid());

    std::string str("AAAA");
    str[0] = (char)((fourCC._fourCC & 0xFF000000) >> 24);
    str[1] = (char)((fourCC._fourCC & 0x00FF0000) >> 16);
    str[2] = (char)((fourCC._fourCC & 0x0000FF00) >> 8);
    str[3] = (char)(fourCC._fourCC & 0x000000FF);

    return str;
}

Util::FourCC Util::FourCC::FromString(const std::string& fourCC)
{
    _assert(4 == fourCC.length());

    return FourCC(uint32_t(fourCC[0] | fourCC[1] << 8 | fourCC[2] << 16 | fourCC[3] << 24));
}

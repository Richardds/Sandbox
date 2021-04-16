// ----------------------------------------------------------------------------------------
//  \file       InputFile.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "IO/InputFile.h"
#include "Core/Exception/IOException.h"

IO::InputFile::InputFile() :
    _isOpen(false),
    _fileSize(0)
{
}

IO::InputFile::InputFile(const std::string& path) :
    _file(path, std::ios::in | std::ios::binary | std::ios::ate),
    _isOpen(false),
    _path(path),
    _fileSize(0)
{
    this->_isOpen = this->_file.is_open();
    if (this->_isOpen)
    {
        this->_fileSize = this->_file.tellg();
        this->Seek(0);
    }
}

IO::InputFile::~InputFile()
{
    if (this->_isOpen)
    {
        this->_file.close();
        // Do not throw exception on unsuccessful file close
    }
}

bool IO::InputFile::Open(const std::string& path)
{
    _Assert(!this->IsOpen())

    this->_file.open(path, std::ios::in | std::ios::binary | std::ios::ate);
    this->_isOpen = this->_file.is_open();
    this->_path = path;
    if (this->_isOpen)
    {
        this->_fileSize = this->_file.tellg();
        this->Seek(0);

        return true;
    }

    return false;
}

void IO::InputFile::Read(std::string& string)
{
    _Assert(this->IsOpen())

    // Read string size
    uint16_t length;
    this->Read(length);

    // Read string into buffer
    std::vector<char> stringBuffer(length);
    this->Read(stringBuffer.data(), length);

    // Transform buffer into string
    string = std::string(stringBuffer.begin(), stringBuffer.end());
}

void IO::InputFile::Read(Util::FourCC& fourCC)
{
    uint32_t value;
    this->Read(value);

    fourCC.SetFromUint32(value);
}

void IO::InputFile::ReadLine(std::string& line, const char delimeter)
{
    _Assert(this->IsOpen())

    std::getline(this->_file, line, this->_file.widen(delimeter));
    if (this->_file.fail())
    {
        throw Core::IOException("Failed to read from file");
    }
}

void IO::InputFile::Seek(const size_t offset)
{
    _Assert(this->IsOpen())

    this->_file.seekg(offset, std::ios::beg);
}

void IO::InputFile::Close()
{
    if (this->_isOpen)
    {
        this->_file.close();
        if (this->_file.fail())
        {
            throw Core::IOException("Failed to close file");
        }
        this->_isOpen = false;
    }
}

// ----------------------------------------------------------------------------------------
//  \file       OutputFile.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "IO/OutputFile.h"
#include "Core/Exception/IOException.h"

IO::OutputFile::OutputFile() :
    _isOpen(false),
    _fileSize(0)
{
}

IO::OutputFile::OutputFile(const std::string& path, const bool append) :
    _file(path, std::ios::out | std::ios::binary | (append ? std::ios::app : std::ios::trunc)),
    _isOpen(false),
    _path(path),
    _fileSize(0)
{
    this->_isOpen = this->_file.is_open();
}

IO::OutputFile::~OutputFile()
{
    if (this->_isOpen)
    {
        this->_file.close();
        // Do not throw exception on unsuccessful file close
    }
}

bool IO::OutputFile::Open(const std::string& path, const bool append)
{
    _Assert(!this->IsOpen())

    this->_file.open(path, std::ios::out | std::ios::binary | (append ? std::ios::app : std::ios::trunc));
    this->_isOpen = this->_file.is_open();
    this->_path = path;

    return this->_isOpen;
}

void IO::OutputFile::Write(const std::string& string)
{
    _Assert(this->IsOpen())

    const size_t size = string.size();

    _Assert(65535 >= size)
        
    // Write string size
    this->Write(static_cast<uint16_t>(size));

    // Write string into file
    this->Write(string.c_str(), size);
}

void IO::OutputFile::Write(const Util::FourCC& fourCC)
{
    const uint32_t value = fourCC.ToUint32();
    this->Write(value);
}

void IO::OutputFile::Close()
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

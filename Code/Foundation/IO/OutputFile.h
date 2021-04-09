// ----------------------------------------------------------------------------------------
//  \file       OutputFile.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Debug.h"
#include "Core/Exception/IOException.h"
#include "Util/FourCC.h"

namespace IO
{
    class EXPORT OutputFile
    {
    public:
        OutputFile();
        OutputFile(const std::string& path, bool append = false);
        virtual ~OutputFile();

        bool Open(const std::string& path, bool append = false);
        bool IsOpen() const;
        std::string GetPath() const;
        size_t GetSize() const;
        bool IsEmpty() const;
        void Write(const std::string& string);
        void Write(const Util::FourCC& fourCC);
        template <typename T>
        void Write(const T& value);
        template <typename T>
        void Write(const T* values, size_t count);
        void Close();

    protected:
        std::ofstream _file;
        bool _isOpen;
        std::string _path;
        size_t _fileSize;
    };

    inline bool OutputFile::IsOpen() const
    {
        return this->_isOpen;
    }

    inline std::string OutputFile::GetPath() const
    {
        return this->_path;
    }

    inline size_t OutputFile::GetSize() const
    {
        return this->_fileSize;
    }

    inline bool OutputFile::IsEmpty() const
    {
        return 0 == this->_fileSize;
    }

    template <typename T>
    void OutputFile::Write(const T& value)
    {
        _Assert(this->IsOpen())

        const size_t size = sizeof(T);
        this->_file.write(reinterpret_cast<const char*>(&value), size);
        if (this->_file.fail())
        {
            throw Core::IOException("Failed to write to file");
        }
        this->_fileSize += size;
    }

    template <typename T>
    void OutputFile::Write(const T* values, const size_t count)
    {
        _Assert(this->IsOpen())

        const size_t size = sizeof(T) * count;
        this->_file.write(reinterpret_cast<const char*>(values), size);
        if (this->_file.fail())
        {
            throw Core::IOException("Failed to write to file");
        }
        this->_fileSize += size;
    }
}

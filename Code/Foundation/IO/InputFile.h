// ----------------------------------------------------------------------------------------
//  \file       InputFile.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Core/Debug.h"
#include "Core/Exception/IOException.h"
#include "Util/FourCC.h"

namespace IO
{
    class EXPORT InputFile
    {
    public:
        InputFile();
        explicit InputFile(const std::string& path);
        virtual ~InputFile();

        bool Open(const std::string& path);
        bool IsOpen() const;
        std::string GetPath() const;
        size_t GetSize() const;
        bool IsEmpty() const;
        bool IsEndOfFile() const;
        std::ifstream& GetStream();
        void Read(std::string& string);
        void Read(Util::FourCC& fourCC);
        template <typename T>
        void Read(T& value);
        template <typename T>
        void Read(T* values, size_t count);
        void ReadLine(std::string& line, char delimeter = '\n');
        void Seek(size_t offset);
        void Close();
        
    protected:
        std::ifstream _file;
        bool _isOpen;
        std::string _path;
        size_t _fileSize;
    };

    inline bool InputFile::IsOpen() const
    {
        return this->_isOpen;
    }

    inline std::string InputFile::GetPath() const
    {
        return this->_path;
    }

    inline size_t InputFile::GetSize() const
    {
        return this->_fileSize;
    }

    inline bool InputFile::IsEmpty() const
    {
        return 0 == this->_fileSize;
    }

    inline bool InputFile::IsEndOfFile() const
    {
        return this->_file.eof();
    }

    inline std::ifstream& InputFile::GetStream()
    {
        return this->_file;
    }

    template <typename T>
    void InputFile::Read(T& value)
    {
        _Assert(this->IsOpen())

        this->_file.read(reinterpret_cast<char*>(&value), sizeof(T));
        if (this->_file.fail())
        {
            throw Core::IOException("Failed to read from file");
        }
    }

    template <typename T>
    void InputFile::Read(T* values, const size_t count)
    {
        _Assert(this->IsOpen())

        this->_file.read(reinterpret_cast<char*>(values), sizeof(T) * count);
        if (this->_file.fail())
        {
            throw Core::IOException("Failed to read from file");
        }
    }
}

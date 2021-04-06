// ----------------------------------------------------------------------------------------
//  \file       Application.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"

namespace App
{
    /// Base class of every application
    class Application
    {
    public:
        Application();
        virtual ~Application();

        virtual bool Open();
        virtual void Run() = 0;
        virtual void Close();
        virtual void SetTitle(const std::string& title);
        const std::string& GetTitle() const;
        void SetVersion(const std::string& version);
        const std::string& GetVersion() const;
        bool IsOpen() const;
        int GetStatusCode() const;

    protected:
        void SetReturnCode(int code);

        std::string _title;
        std::string _version;
        bool _isOpen;
        int _statusCode;
    };

    inline void Application::SetTitle(const std::string& title)
    {
        this->_title = title;
    }

    inline const std::string& Application::GetTitle() const
    {
        return this->_title;
    }

    inline void Application::SetVersion(const std::string& version)
    {
        this->_version = version;
    }

    inline const std::string& Application::GetVersion() const
    {
        return this->_version;
    }

    inline bool Application::IsOpen() const
    {
        return this->_isOpen;
    }

    inline int Application::GetStatusCode() const
    {
        return this->_statusCode;
    }

    inline void Application::SetReturnCode(const int code)
    {
        this->_statusCode = code;
    }
}

#pragma once

#include <string>

namespace App
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual bool Open();
		virtual void Run() = 0;
		virtual void Close();
		virtual void SetTitle(const std::string& title);
		[[nodiscard]] const std::string& GetTitle() const;
		void SetVersion(const std::string& version);
		[[nodiscard]] const std::string& GetVersion() const;
		[[nodiscard]] bool IsOpen() const;
		[[nodiscard]] int GetStatusCode() const;

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

#pragma once

#include <memory>

#include "Application.h"
#include "../Graphics/Window.h"
#include "../Timing/Time.h"

namespace App
{
	class RenderApplication : public Application
	{
	public:
		RenderApplication();
		virtual ~RenderApplication();

		bool Open() override;
		void Run() override;
		void Close() override;

	protected:
		virtual void OnConfigureContext();
		virtual void OnProcessInput();
		void PrintDeviceInfo() const;
		void OnInitializeFrame();
		virtual void OnUpdateLogic();
		virtual void OnUpdateFrame();
		void SetQuitRequested(bool isQuitRequested);
		[[nodiscard]] bool IsQuitRequested() const;
		[[nodiscard]] Timing::Time GetTime() const;
		[[nodiscard]] Timing::Duration GetFrameTime() const;
		[[nodiscard]] float GetFrameDelta() const;

	private:
		void UpdateTime();

		std::shared_ptr<Graphics::Window> _window;
		Timing::Time _time;
		Timing::Duration _frameTime;
		bool _isQuitRequested;
	};

	inline void RenderApplication::SetQuitRequested(const bool isQuitRequested)
	{
		this->_isQuitRequested = isQuitRequested;
	}

	inline bool RenderApplication::IsQuitRequested() const
	{
		return (this->_isQuitRequested || this->_window->IsCloseRequested());
	}

	inline Timing::Time RenderApplication::GetTime() const
	{
		return this->_time;
	}

	inline Timing::Duration RenderApplication::GetFrameTime() const
	{
		return this->_frameTime;
	}
}

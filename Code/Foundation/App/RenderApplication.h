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

		bool Open() override;
		void Run() override;
		void Close() override;
		void SetTitle(const std::string& title) override;
		void UpdateTitleStats() const;

	protected:
		virtual void OnConfigureContext();
		virtual void OnProcessInput() = 0;
		void PrintDeviceInfo() const;
		void SetVSyncEnabled(bool enabled);
		void OnInitializeFrame();
		virtual void OnUpdateLogic() = 0;
		virtual void OnUpdateFrame() = 0;
		void SetQuitRequested(bool isQuitRequested);
		[[nodiscard]] bool IsQuitRequested() const;
		[[nodiscard]] Timing::Time GetTime() const;
		[[nodiscard]] Timing::Duration GetFrameTime() const;
		[[nodiscard]] float GetFrameDelta() const;

	private:
		void UpdateTiming();

		std::shared_ptr<Graphics::Window> _window;
		Timing::Time _time;
		Timing::Duration _frameTime;
		float _currentSecond;
		unsigned int _frameCount;
		unsigned int _lastFrameCount;
		bool _isQuitRequested;
		bool _vSyncEnabled;
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

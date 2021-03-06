// ----------------------------------------------------------------------------------------
//  \file       RenderApplication.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "App/Application.h"
#include "Graphics/Window.h"
#include "Timing/Time.h"

namespace App
{
    /// Base class of every application with rendering capabilities
    class EXPORT RenderApplication : public Application
    {
    public:
        struct Stats
        {
            unsigned int framePerSecond;
            float frameTimeAverage;
        };

        RenderApplication();

        bool Open() override;
        void Run() override;
        void Close() override;
        void SetTitle(const std::string& title) override;

    protected:
        virtual void OnConfigureContext();
        virtual void OnProcessInput() = 0;
        void PrintDeviceInfo() const;
        void SetVSyncEnabled(bool enabled);
        void SetWireframeModeEnabled(bool enabled);
        void OnInitializeFrame();
        virtual void OnUpdateLogic() = 0;
        virtual void OnUpdateFrame() = 0;
        void SetQuitRequested(bool isQuitRequested);
        bool IsQuitRequested() const;
        Timing::Time GetTime() const;
        Timing::Duration GetFrameTime() const;
        float GetFrameDelta() const;

        Stats _stats;

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
        bool _wireframeModeEnabled;
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

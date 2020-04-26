#pragma once

#include <memory>

#include "Application.h"
#include "../Timing/Time.h"
#include "../Graphics/Window.h"

namespace App
{

    class RenderApplication : public Application
    {
    public:
        RenderApplication();
        virtual ~RenderApplication();
        virtual bool Open();
        virtual void Run();
        virtual void Close();

    protected:
        virtual void OnConfigureContext();
        virtual void OnProcessInput();
        void PrintDeviceInfo() const;
        void OnInitializeFrame();
        virtual void OnUpdateLogic();
        virtual void OnUpdateFrame();
        void SetQuitRequested(bool isQuitRequested);
        bool IsQuitRequested() const;
        Timing::Time GetTime() const;
        Timing::Duration GetFrameTime() const;

    private:
        void UpdateTime();

        Timing::Time _time;
        Timing::Duration _frameTime;
        bool _isQuitRequested;

        std::shared_ptr<Graphics::Window> window;
    };

    inline void App::RenderApplication::SetQuitRequested(bool isQuitRequested)
    {
        this->_isQuitRequested = isQuitRequested;
    }

    inline bool App::RenderApplication::IsQuitRequested() const
    {
        return (this->_isQuitRequested || this->window->IsCloseRequested());
    }

    inline Timing::Time App::RenderApplication::GetTime() const
    {
        return this->_time;
    }

    inline Timing::Duration RenderApplication::GetFrameTime() const
    {
        return this->_frameTime;
    }

}

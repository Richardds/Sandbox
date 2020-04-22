#pragma once

#include <memory>
#include <App/RenderApplication.h>
#include <Graphics/Scene.h>

namespace GunnerBoi
{

    class GunnerBoiApplication : public App::RenderApplication
    {
    public:
        GunnerBoiApplication();
        virtual ~GunnerBoiApplication();
        bool Open();
        void Close();

    protected:
        void OnProcessInput();
        void OnUpdateLogic();
        void OnUpdateFrame();

    private:
        void PrintStartupMessage();

        std::shared_ptr<Graphics::Scene> _scene;
    };

}

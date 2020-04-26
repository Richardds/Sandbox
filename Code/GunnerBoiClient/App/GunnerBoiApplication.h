#pragma once

#include <memory>
#include <App/RenderApplication.h>

#include "../Game/GunnerBoiScene.h"

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
        std::shared_ptr<GunnerBoiScene> _scene;
    };

}

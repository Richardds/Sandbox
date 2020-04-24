#pragma once

#include <App/Application.h>

namespace GunnerBoi
{

    class MeshExporterApplication : public App::Application
    {
    public:
        MeshExporterApplication();
        virtual ~MeshExporterApplication();
        bool Open();
        void Close();
    };

}

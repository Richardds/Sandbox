#include "App/MeshExporterApplication.h"

using namespace GunnerBoi;

int main()
{
    MeshExporterApplication app;
    app.SetTitle("Mesh Exporter");
    app.SetVersion("0.0.1 dev");

    if (app.Open())
    {
        app.Run();
        app.Close();
    }

    return app.GetStatusCode();
}

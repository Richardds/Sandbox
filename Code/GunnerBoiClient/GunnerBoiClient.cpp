#include "App/GunnerBoiApplication.h"

using namespace GunnerBoi;

int main()
{
    GunnerBoiApplication app;
    app.SetTitle("Gunner Boi");
    app.SetVersion("0.0.1 dev");

    if (app.Open())
    {
        app.Run();
        app.Close();
    }

    return app.GetStatusCode();
}

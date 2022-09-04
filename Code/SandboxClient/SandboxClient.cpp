// ----------------------------------------------------------------------------------------
//  \file       SandboxClient.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "App/SandboxApplication.h"

using namespace Sandbox;

int main()
{
    SandboxApplication app;
    app.SetTitle("Sandbox");
    app.SetVersion("0.1.5-dev");

    if (app.Open())
    {
        app.Run();
        app.Close();
    }

    return app.GetStatusCode();
}

// ----------------------------------------------------------------------------------------
//  \file       Test.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include <Precompiled.h>

#include "App/TestApplication.h"

using namespace Sandbox;

int main()
{
    TestApplication app;
    app.SetTitle("Test");
    app.SetVersion("unversioned");

    if (app.Open())
    {
        app.Run();
        app.Close();
    }

    return app.GetStatusCode();
}

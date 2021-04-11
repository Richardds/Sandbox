// ----------------------------------------------------------------------------------------
//  \file       MeshExporter.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include <IO/Console.h>

#include "App/MeshExporterApplication.h"

using namespace Sandbox;

int main(const int argc, char* argv[])
{
    MeshExporterApplication app;
    app.SetTitle("Mesh Exporter");
    app.SetVersion("0.0.1 dev");

    if (argc != 3)
    {
        IO::Console::Instance().Error("Invalid number of arguments provided\n");
        return EXIT_FAILURE;
    }

    app.SetInputFilePath(argv[1]);
    app.SetOutputFilePath(argv[2]);

    if (app.Open())
    {
        app.Run();
        app.Close();
    }

    return app.GetStatusCode();
}

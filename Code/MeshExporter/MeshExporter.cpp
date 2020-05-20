#include "App/MeshExporterApplication.h"
#include "IO/Console.h"

using namespace GunnerBoi;

int main(int argc, char* argv[])
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

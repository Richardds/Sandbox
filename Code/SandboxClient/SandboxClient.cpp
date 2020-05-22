#include <Precompiled.h>

#include "App/SandboxApplication.h"

using namespace Sandbox;

int main()
{
	SandboxApplication app;
	app.SetTitle("Sandbox");
	app.SetVersion("0.0.1 dev");

	if (app.Open())
	{
		app.Run();
		app.Close();
	}

	return app.GetStatusCode();
}

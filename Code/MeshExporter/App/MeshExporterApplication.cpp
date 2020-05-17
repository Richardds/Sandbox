#include "MeshExporterApplication.h"

GunnerBoi::MeshExporterApplication::MeshExporterApplication()
{
}

GunnerBoi::MeshExporterApplication::~MeshExporterApplication()
{
}

bool GunnerBoi::MeshExporterApplication::Open()
{
	if (Application::Open())
	{
		// TODO

		return true;
	}

	return false;
}

void GunnerBoi::MeshExporterApplication::Close()
{
	Application::Close();
}

#include "MeshExporterApplication.h"

#include "IO/Console.h"
#include "Util/Exporters/AssimpExporter.h"

bool Sandbox::MeshExporterApplication::Open()
{
	if (Application::Open())
	{
		if (this->_fbxFilePath.empty())
		{
			this->SetReturnCode(EXIT_FAILURE);
			IO::Console::Instance().Error("Input FBX file path is not set\n");
			return false;
		}

		if (this->_modelFilePath.empty())
		{
			this->SetReturnCode(EXIT_FAILURE);
			IO::Console::Instance().Error("Output model file path is not set\n");
			return false;
		}

		std::ifstream fbxFile;
		fbxFile.open(this->_fbxFilePath, std::ios::binary | std::ios::ate);

		if (!fbxFile.is_open())
		{
			this->SetReturnCode(EXIT_FAILURE);
			IO::Console::Instance().Error("Failed to open input FBX file\n");
			return false;
		}

		this->_modelFile.open(this->_modelFilePath, std::ios::binary);

		if (!this->_modelFile.is_open())
		{
			fbxFile.close();
			this->SetReturnCode(EXIT_FAILURE);
			IO::Console::Instance().Error("Failed to open output model file\n");
			return false;
		}

		// Load FBX file data into memory
		const std::streamsize fbxFileSize = fbxFile.tellg();
		fbxFile.seekg(0, std::ios::beg);
		this->_fbxDataBuffer.resize(fbxFileSize);
		fbxFile.read(this->_fbxDataBuffer.data(), fbxFileSize);
		fbxFile.close();

		return true;
	}

	return false;
}

void Sandbox::MeshExporterApplication::Run()
{
	Util::AssimpExporter exporter;

	if (!exporter.Load(this->_fbxDataBuffer))
	{
		IO::Console::Instance().Error("Failed to parse FBX file\n");
		return;
	}

	exporter.Export(this->_modelFile);

	IO::Console::Instance().Info("Model '%s' successfully exported\n", this->_modelFilePath.c_str());
}

void Sandbox::MeshExporterApplication::Close()
{
	this->_modelFile.close();
	
	Application::Close();
}

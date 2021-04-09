// ----------------------------------------------------------------------------------------
//  \file       MeshExporterApplication.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include <IO/Console.h>

#include "App/MeshExporterApplication.h"
#include "Exporters/AssimpExporter.h"
#include "IO/InputFile.h"

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

        IO::InputFile fbxFile(this->_fbxFilePath);
        if (!fbxFile.IsOpen())
        {
            IO::Console::Instance().Error("Failed to open input FBX file\n");
            this->SetReturnCode(EXIT_FAILURE);
            return false;
        }

        if (!this->_modelFile.Open(this->_modelFilePath))
        {
            IO::Console::Instance().Error("Failed to open output model file\n");
            this->SetReturnCode(EXIT_FAILURE);
            return false;
        }

        // Load FBX file data into memory
        const size_t fbxFileSize = fbxFile.GetSize();
        this->_fbxDataBuffer.resize(fbxFileSize);
        fbxFile.Read(this->_fbxDataBuffer.data(), fbxFileSize);

        fbxFile.Close();

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

    this->_modelFile.Close();

    IO::Console::Instance().Info("Model '%s' successfully exported\n", this->_modelFilePath.c_str());
}

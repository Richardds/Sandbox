// ----------------------------------------------------------------------------------------
//  \file       MeshExporterApplication.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include <Precompiled.h>
#include <App/Application.h>
#include <IO/OutputFile.h>

namespace Sandbox
{
    /// Mesh exporter application overrider class
    class MeshExporterApplication : public App::Application
    {
    public:
        MeshExporterApplication() = default;

        bool Open() override;
        void SetInputFilePath(const std::string& path);
        void SetOutputFilePath(const std::string& path);
        void Run() override;

    private:
        std::string _fbxFilePath;
        std::string _modelFilePath;
        std::vector<char> _fbxDataBuffer;
        IO::OutputFile _modelFile;
    };

    inline void MeshExporterApplication::SetInputFilePath(const std::string& path)
    {
        this->_fbxFilePath = path;
    }

    inline void MeshExporterApplication::SetOutputFilePath(const std::string& path)
    {
        this->_modelFilePath = path;
    }
}

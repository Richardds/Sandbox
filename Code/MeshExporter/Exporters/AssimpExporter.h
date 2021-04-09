// ----------------------------------------------------------------------------------------
//  \file       AssimpExporter.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include <Precompiled.h>
#include <IO/OutputFile.h>

namespace Util
{
    /// Custom model format exporter which uses Assimp library
    class AssimpExporter
    {
    public:
        AssimpExporter();

        bool Load(const std::vector<char>& buffer);
        void Export(IO::OutputFile& outputFile) const;

    private:
        static std::string ParseAssetName(const aiString& assetPath);

        void WriteNode(IO::OutputFile& file, const aiNode* node) const;
        void WriteMaterial(IO::OutputFile& file, const aiMaterial* material) const;
        void WriteMesh(IO::OutputFile& file, const aiMesh* mesh) const;

        Assimp::Importer _importer;
        const aiScene* _scene;
    };
}

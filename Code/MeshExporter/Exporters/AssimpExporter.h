// ----------------------------------------------------------------------------------------
//  \file       AssimpExporter.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include <Precompiled.h>

namespace Util
{
    /// Custom model format exporter which uses Assimp library
    class AssimpExporter
    {
    public:
        AssimpExporter();

        bool Load(const std::vector<char>& buffer);
        void Export(std::ofstream& outputFile) const;

    private:
        template <typename T>
        void Write(std::ofstream& file, T value) const;
        void WriteString(std::ofstream& outputFile, const std::string& string) const;
        void WriteNode(std::ofstream& file, aiNode* node) const;
        void WriteMaterial(std::ofstream& file, aiMaterial* material) const;
        void WriteMesh(std::ofstream& file, aiMesh* mesh) const;
        std::string ParseAssetName(const aiString& assetPath) const;

        Assimp::Importer _importer;
        const aiScene* _scene;
    };

    template <typename T>
    void AssimpExporter::Write(std::ofstream& file, T value) const
    {
        file.write(reinterpret_cast<const char*>(&value), sizeof(T));
    }
}

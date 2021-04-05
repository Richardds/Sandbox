// ----------------------------------------------------------------------------------------
//  \file       ModelLoader.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/Material.h"
#include "Graphics/Model.h"
#include "Graphics/VertexAttributeConfig.h"

namespace Util
{
    /// Model loader which uses our custom format
    class ModelLoader
    {
    public:
        ModelLoader();
        virtual ~ModelLoader() = default;

        void Load(std::shared_ptr<Graphics::Model>& model, std::ifstream& file);

    private:
        template <typename T>
        void Read(T* value, std::ifstream& file) const;
        std::string ReadString(std::ifstream& file) const;
        std::shared_ptr<Graphics::Material> ReadMaterial(std::ifstream& file) const;
        std::shared_ptr<Graphics::TexturedMesh> ReadMesh(std::ifstream& file) const;

        Graphics::VertexAttributeConfig _attributesTemplate;
    };

    template <typename T>
    void ModelLoader::Read(T* value, std::ifstream& file) const
    {
        file.read(reinterpret_cast<char*>(value), sizeof(T));
    }
}

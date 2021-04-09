// ----------------------------------------------------------------------------------------
//  \file       ModelLoader.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/Material.h"
#include "Graphics/Model.h"
#include "Graphics/VertexAttributeConfig.h"
#include "IO/InputFile.h"

namespace Util
{
    /// Model loader which uses our custom format
    class EXPORT ModelLoader
    {
    public:
        ModelLoader();
        virtual ~ModelLoader() = default;

        void Load(std::shared_ptr<Graphics::Model>& model, IO::InputFile& file) const;

    private:
        std::shared_ptr<Graphics::TexturedMesh> ReadMesh(IO::InputFile& file) const;
        std::shared_ptr<Graphics::Material> ReadMaterial(IO::InputFile& file) const;

        Graphics::VertexAttributeConfig _attributesTemplate;
    };
}

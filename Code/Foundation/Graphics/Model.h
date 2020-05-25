// ----------------------------------------------------------------------------------------
//  \file       Model.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/TexturedMesh.h"
#include "Graphics/Shaders/EntityShader.h"

namespace Graphics
{
    /// Holds model information of multiple meshes
    class Model
    {
    public:
        enum class State
        {
            Initial,
            Loaded
        };

        Model();
        void Render(const std::shared_ptr<EntityShader>& shader);
        [[nodiscard]] State GetState() const;
        void AddMesh(const std::string& name, const std::shared_ptr<TexturedMesh>& mesh);
        void AddMesh(const std::string& name, const std::shared_ptr<Mesh>& mesh);
        [[nodiscard]] std::shared_ptr<TexturedMesh> GetMesh(const std::string& name) const;
        [[nodiscard]] std::unordered_map<std::string, std::shared_ptr<TexturedMesh>> GetMeshes() const;
        void FinishLoading();

    private:
        State _state;
        std::unordered_map<std::string, std::shared_ptr<TexturedMesh>> _meshes;
    };

    inline Model::State Model::GetState() const
    {
        return this->_state;
    }
}

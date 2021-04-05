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
        virtual ~Model() = default;

        void Render(const std::shared_ptr<EntityShader>& shader);
        [[nodiscard]] State GetState() const;
        void AddMesh(const std::string& name, const std::shared_ptr<TexturedMesh>& mesh);
        void AddMesh(const std::string& name, const std::shared_ptr<Mesh>& mesh);
        [[nodiscard]] std::shared_ptr<TexturedMesh> GetMesh(const std::string& name) const;
        [[nodiscard]] bool Empty() const;
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

    inline bool Model::Empty() const
    {
        return this->_meshes.empty();
    }

    inline std::unordered_map<std::string, std::shared_ptr<TexturedMesh>> Model::GetMeshes() const
    {
        return this->_meshes;
    }

    inline void Model::FinishLoading()
    {
        _Assert(State::Initial == this->_state);

        this->_state = State::Loaded;
    }
}

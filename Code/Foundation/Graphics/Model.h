#pragma once

#include <unordered_map>
#include <string>

#include "Mesh.h"

namespace Graphics
{

    class Model
    {
    public:
        enum class State {
            INITIAL,
            LOADED
        };

        Model();
        virtual ~Model();
        void Render(std::shared_ptr<EntityShader> shader);
        State GetState() const;
        void AddMesh(const std::string& name, std::shared_ptr<Mesh> mesh);
        std::shared_ptr<Mesh> GetMesh(const std::string& name) const;
        std::unordered_map<std::string, std::shared_ptr<Mesh>> GetMeshes() const;
        void FinishLoading();

    private:
        State _state;
        std::unordered_map<std::string, std::shared_ptr<Mesh>> _meshes;
    };

    inline Graphics::Model::State Graphics::Model::GetState() const
    {
        return this->_state;
    }

}

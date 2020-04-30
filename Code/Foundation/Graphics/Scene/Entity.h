#pragma once

#include "../Attributes/HasPosition.h"
#include "../Attributes/HasRotation.h"
#include "../Attributes/HasScale.h"
#include "../Model.h"
#include "../Shaders/EntityShader.h"

namespace Graphics
{

    class Entity : public HasPosition, public HasRotation, public HasScale
    {
    public:
        Entity();
        Entity(Math::Vector3f position, float rotX = 0.0f, float rotY = 0.0f, float rotZ = 0.0f);
        virtual ~Entity();
        std::shared_ptr<Model> GetModel() const;
        void SetModel(std::shared_ptr<Model> model);
        virtual void Render(std::shared_ptr<EntityShader> shader);

    private:
        std::shared_ptr<Model> _model;
    };

    inline std::shared_ptr<Model> Entity::GetModel() const
    {
        return this->_model;
    }

    inline void Entity::SetModel(std::shared_ptr<Model> model)
    {
        this->_model = model;
    }

}

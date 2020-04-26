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
        Entity(std::shared_ptr<Model> model);
        virtual ~Entity();
        virtual void Render(std::shared_ptr<EntityShader> shader);
        std::shared_ptr<Model> getModel() const;

    private:
        std::shared_ptr<Model> _model;
    };

    inline std::shared_ptr<Model> Entity::getModel() const
    {
        return this->_model;
    }

}

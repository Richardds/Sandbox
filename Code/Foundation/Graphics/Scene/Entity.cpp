#include "Entity.h"
#include "../../Math/Utils.h"

Graphics::Entity::Entity(std::shared_ptr<Model> model) :
    _model(model)
{
}

Graphics::Entity::Entity(std::shared_ptr<Model> model, Math::Vector3f position, float rotX, float rotY, float rotZ, float scale) :
    HasPosition(position),
    HasRotation(rotX, rotY, rotZ),
    HasScale(scale),
    _model(model)
{
}

Graphics::Entity::~Entity()
{
}

void Graphics::Entity::Render(std::shared_ptr<Graphics::EntityShader> shader)
{
    if (this->_model->GetMeshes().size() == 0) {
        return;
    }

    shader->LoadEntityTransformation(
        Math::transformationMatrix(
            this->_position,
            this->_rotX, this->_rotY, this->_rotZ,
            this->_scale
        )
    );

    this->_model->Render();
}

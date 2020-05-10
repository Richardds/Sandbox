#include "Entity.h"
#include "../../Math/Utils.h"

Graphics::Entity::Entity()
{
}

Graphics::Entity::Entity(Math::Vector3f position, float rotX, float rotY, float rotZ) :
    HasPosition(position),
    HasRotation(rotX, rotY, rotZ)
{
}

Graphics::Entity::~Entity()
{
}

void Graphics::Entity::Render(std::shared_ptr<Graphics::EntityShader> shader)
{
    if (!this->_model || this->_model->GetMeshes().size() == 0) {
        return;
    }

    shader->LoadWorldTransformation(
        Math::TransformationMatrix(
            this->_position,
            this->_rotX, this->_rotY, this->_rotZ,
            this->_scale
        )
    );

    this->_model->Render(shader);
}

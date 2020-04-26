#include "Entity.h"
#include "../../Math/Utils.h"

Graphics::Entity::Entity()
{
}

Graphics::Entity::Entity(Math::Vector3f position) :
    HasPosition(position)
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

    shader->LoadEntityTransformation(
        Math::transformationMatrix(
            this->_position,
            this->_rotX, this->_rotY, this->_rotZ,
            this->_scale
        )
    );

    this->_model->Render(shader);
}

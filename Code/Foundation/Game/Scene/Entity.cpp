// ----------------------------------------------------------------------------------------
//  \file       Entity.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Scene/Entity.h"
#include "Math/Utils.h"

Graphics::Entity::Entity()
{
}

Graphics::Entity::Entity(const Math::Vector3f& position, const float rotX, const float rotY, const float rotZ) :
    HasPosition(position),
    HasRotation(rotX, rotY, rotZ)
{
}

void Graphics::Entity::Render(const std::shared_ptr<EntityShader>& shader) const
{
    if (!this->_model || this->_model->GetMeshes().empty())
    {
        return;
    }

    shader->LoadWorldTransformation(
        Math::TransformationMatrix(
            this->_position,
            this->_rotationX, this->_rotationY, this->_rotationZ,
            this->_scale
        )
    );

    this->_model->Render(shader);
}

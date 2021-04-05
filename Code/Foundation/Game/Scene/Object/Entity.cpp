// ----------------------------------------------------------------------------------------
//  \file       Entity.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Scene/Object/Entity.h"
#include "Math/MathUtils.h"

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
    if (!this->_model || this->_model->Empty())
    {
        return;
    }

    shader->LoadWorldTransformation(
        Math::TransformationMatrix3D(
            this->_position,
            this->_rotationX, this->_rotationY, this->_rotationZ,
            this->_scale
        )
    );

    this->_model->Render(shader);
}

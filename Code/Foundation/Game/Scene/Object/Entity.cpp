// ----------------------------------------------------------------------------------------
//  \file       Entity.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Game/Scene/Object/Entity.h"
#include "Math/MathUtils.h"

Graphics::Entity::Entity(const Math::Vector3f& position) :
    HasPosition3D(position)
{
}

Graphics::Entity::Entity(const Math::Vector3f& position, const Math::Vector3f& rotation) :
    HasPosition3D(position),
    HasRotation3D(rotation)
{
}

void Graphics::Entity::Render(const std::shared_ptr<EntityShader>& shader) const
{
    if (!this->_model || this->_model->IsEmpty())
    {
        return;
    }

    shader->LoadWorldTransformation(Math::TransformationMatrix3D(this->_position, this->_rotation, this->_scale));

    this->_model->Render(shader);
}

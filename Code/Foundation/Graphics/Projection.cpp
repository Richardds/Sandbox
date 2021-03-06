// ----------------------------------------------------------------------------------------
//  \file       Projection.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Graphics/Projection.h"
#include "Math/MathUtils.h"

Graphics::Projection::Projection(const float aspectRatio, const float fieldOfView, const float nearPlane,
                                 const float farPlane) :
    _aspectRatio(aspectRatio),
    _fieldOfView(fieldOfView),
    _nearPlane(nearPlane),
    _farPlane(farPlane)
{
}

Math::Matrix4f Graphics::Projection::GetMatrix() const
{
    return Math::ProjectionMatrix3D(this->_aspectRatio, this->_fieldOfView, this->_nearPlane, this->_farPlane);
}

// ----------------------------------------------------------------------------------------
//  \file       MathUtils.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Math/MathUtils.h"

Math::Matrix4f Math::ProjectionMatrix3D(const float aspectRatio, const float fieldOfView, const float nearPlane,
                                      const float farPlane)
{
    return glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);
}

Math::Matrix4f Math::ViewMatrix3D(const Vector3f& position, const float rotationX, const float rotationY)
{
    Matrix4f viewMatrix(1.0f);
    viewMatrix = rotate(viewMatrix, glm::radians(rotationX), Vector3f(1.0f, 0.0f, 0.0f));
    viewMatrix = rotate(viewMatrix, glm::radians(rotationY), Vector3f(0.0f, 1.0f, 0.0f));
    viewMatrix = translate(viewMatrix, -position);

    return viewMatrix;
}

Math::Matrix4f Math::TransformationMatrix3D(const Vector3f& position, const float rotationX, const float rotationY,
                                          const float rotationZ, const float scale)
{
    Matrix4f transformationMatrix(1.0f);
    transformationMatrix = translate(transformationMatrix, position);
    transformationMatrix = rotate(transformationMatrix, glm::radians(rotationX), Vector3f(1.0f, 0.0f, 0.0f));
    transformationMatrix = rotate(transformationMatrix, glm::radians(rotationY), Vector3f(0.0f, 1.0f, 0.0f));
    transformationMatrix = rotate(transformationMatrix, glm::radians(rotationZ), Vector3f(0.0f, 0.0f, 1.0f));
    transformationMatrix = glm::scale(transformationMatrix, Vector3f(scale));

    return transformationMatrix;
}

Math::Matrix4f Math::TranslationMatrix3D(const Vector3f& position)
{
    Matrix4f translationMatrix(1.0f);
    translationMatrix = translate(translationMatrix, position);

    return translationMatrix;
}

Math::Matrix4f Math::RotationMatrix3D(const float rotationX, const float rotationY, const float rotationZ)
{
    Matrix4f rotationMatrix(1.0f);
    rotationMatrix = rotate(rotationMatrix, glm::radians(rotationX), Vector3f(1.0f, 0.0f, 0.0f));
    rotationMatrix = rotate(rotationMatrix, glm::radians(rotationY), Vector3f(0.0f, 1.0f, 0.0f));
    rotationMatrix = rotate(rotationMatrix, glm::radians(rotationZ), Vector3f(0.0f, 0.0f, 1.0f));

    return rotationMatrix;
}

Math::Matrix4f Math::ScaleMatrix3D(const float scale)
{
    Matrix4f scaleMatrix(1.0f);
    scaleMatrix = glm::scale(scaleMatrix, Vector3f(scale));

    return scaleMatrix;
}

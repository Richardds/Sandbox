#include "Utils.h"

Math::Matrix4f Math::ProjectionMatrix(float aspectRatio, float fieldOfView, float nearPlane, float farPlane)
{
    return glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);
}

Math::Matrix4f Math::ViewMatrix(const Vector3f& position, float rotX, float rotY)
{
    Matrix4f viewMatrix(1.0f);
    viewMatrix = glm::rotate(viewMatrix, glm::radians(-rotX), Math::Vector3f(1.0f, 0.0f, 0.0f));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(-rotY), Math::Vector3f(0.0f, 1.0f, 0.0f));
    viewMatrix = glm::translate(viewMatrix, -position);

    return viewMatrix;
}

Math::Matrix4f Math::TransformationMatrix(const Vector3f& position, float rotX, float rotY, float rotZ, float scale)
{
    Matrix4f tranformationMatrix(1.0f);
    tranformationMatrix = glm::translate(tranformationMatrix, position);
    tranformationMatrix = glm::rotate(tranformationMatrix, glm::radians(rotX), Vector3f(1.0f, 0.0f, 0.0f));
    tranformationMatrix = glm::rotate(tranformationMatrix, glm::radians(rotY), Vector3f(0.0f, 1.0f, 0.0f));
    tranformationMatrix = glm::rotate(tranformationMatrix, glm::radians(rotZ), Vector3f(0.0f, 0.0f, 1.0f));
    tranformationMatrix = glm::scale(tranformationMatrix, Vector3f(scale));

    return tranformationMatrix;
}

Math::Matrix4f Math::TranslationMatrix(const Vector3f& position)
{
    Matrix4f translationMatrix(1.0f);
    translationMatrix = glm::translate(translationMatrix, position);

    return translationMatrix;
}

Math::Matrix4f Math::RotationMatrix(float rotX, float rotY, float rotZ)
{
    Matrix4f rotationMatrix(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotX), Vector3f(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotY), Vector3f(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotZ), Vector3f(0.0f, 0.0f, 1.0f));

    return rotationMatrix;
}

Math::Matrix4f Math::ScaleMatrix(float scale)
{
    Matrix4f scaleMatrix(1.0f);
    scaleMatrix = glm::scale(scaleMatrix, Vector3f(scale));

    return scaleMatrix;
}

float Math::LookAt(const Vector2f& position, const Vector2f& target)
{
    Vector2f diff = target - position;
    return glm::degrees(glm::atan(-diff.y, diff.x)) + 90.0f;
}

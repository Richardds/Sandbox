#include "Utils.h"

Math::Matrix4f Math::projectionMatrix(float aspectRatio, float fieldOfView, float nearPlane, float farPlane)
{
    return glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);
}

Math::Matrix4f Math::viewMatrix(Vector3f position, float rotX, float rotY)
{
    Matrix4f viewMatrix(1.0f);
    viewMatrix = glm::rotate(viewMatrix, glm::radians(-rotX), Math::Vector3f(1.0f, 0.0f, 0.0f));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(-rotY), Math::Vector3f(0.0f, 1.0f, 0.0f));
    viewMatrix = glm::translate(viewMatrix, -position);

    return viewMatrix;
}

Math::Matrix4f Math::transformationMatrix(const Vector3f& position, float rotX, float rotY, float rotZ, float scale)
{
    Matrix4f tranformationMatrix(1.0f);
    tranformationMatrix = glm::translate(tranformationMatrix, position);
    tranformationMatrix = glm::rotate(tranformationMatrix, glm::radians(rotX), Vector3f(1.0f, 0.0f, 0.0f));
    tranformationMatrix = glm::rotate(tranformationMatrix, glm::radians(rotY), Vector3f(0.0f, 1.0f, 0.0f));
    tranformationMatrix = glm::rotate(tranformationMatrix, glm::radians(rotZ), Vector3f(0.0f, 0.0f, 1.0f));
    tranformationMatrix = glm::scale(tranformationMatrix, Vector3f(scale));

    return tranformationMatrix;
}

float Math::LookAt(const Vector2f& position, const Vector2f& target)
{
    Vector2f diff = target - position;
    return glm::degrees(glm::atan(-diff.y, diff.x)) - 90.0f;
}

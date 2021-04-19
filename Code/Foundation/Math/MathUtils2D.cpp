// ----------------------------------------------------------------------------------------
//  \file       MathUtils.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Math/MathUtils2D.h"

Math::Matrix3f Math::TransformationMatrix2D(const Vector2f& position, const float rotation, const float scale)
{
    Matrix3f transformationMatrix(1.0f);
    transformationMatrix = translate(transformationMatrix, position);
    transformationMatrix = rotate(transformationMatrix, glm::radians(rotation));
    transformationMatrix = glm::scale(transformationMatrix, Vector2f(scale));

    return transformationMatrix;
}

Math::Matrix3f Math::TranslationMatrix2D(const Vector2f& position)
{
    Matrix3f translationMatrix(1.0f);
    translationMatrix = translate(translationMatrix, position);

    return translationMatrix;
}

Math::Matrix3f Math::RotationMatrix2D(const float rotation)
{
    Matrix3f rotationMatrix(1.0f);
    rotationMatrix = rotate(rotationMatrix, glm::radians(rotation));

    return rotationMatrix;
}

Math::Matrix3f Math::ScaleMatrix2D(const float scale)
{
    Matrix3f scaleMatrix(1.0f);
    scaleMatrix = glm::scale(scaleMatrix, Vector2f(scale));

    return scaleMatrix;
}

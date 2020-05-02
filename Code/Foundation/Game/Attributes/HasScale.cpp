#include "../Attributes/HasRotation.h"
#include "../Attributes/HasScale.h"

Graphics::HasScale::HasScale() :
    _scale(1.0f)
{
}

Graphics::HasScale::HasScale(float scale) :
    _scale(scale)
{
}

void Graphics::HasScale::increaseScale(float scale)
{
    this->_scale += scale;
}

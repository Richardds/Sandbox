#include "Water.h"
#include "../../Math/Utils.h"

Graphics::Water::Water(std::shared_ptr<Mesh> mesh) :
    _mesh(mesh)
{
}

Graphics::Water::Water(std::shared_ptr<Mesh> mesh, Math::Vector3f position) :
    _mesh(mesh),
    HasPosition(position)
{
}

Graphics::Water::~Water()
{
}

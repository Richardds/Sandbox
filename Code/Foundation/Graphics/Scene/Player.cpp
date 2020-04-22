#include <cmath>

#include "Player.h"
#include "../../Math/Utils.h"
#include "../../Core/Debug.h"

Graphics::Player::Player(std::shared_ptr<Model> model) :
    Entity(model)
{
}

Graphics::Player::Player(std::shared_ptr<Model> model, Math::Vector3f position) :
    Entity(model, position)
{
}

Graphics::Player::~Player()
{
}

void Graphics::Player::Move(float distance)
{
    this->increasePosition(
        -std::sinf(glm::radians(this->_rotY)) * distance,
        0.0f,
        std::cosf(glm::radians(this->_rotY)) * distance
    );
}

void Graphics::Player::LookAt(std::shared_ptr<HasPosition> target)
{
    _assert(target);

    this->_rotY = Math::LookAt(
        Math::Vector2f(this->_position.x, this->_position.z),
        Math::Vector2f(target->getPosition().x, target->getPosition().z)
    );
}

#include <cmath>

#include "Player.h"
#include "../../Math/Utils.h"
#include "../../Core/Debug.h"

Graphics::Player::Player()
{
}

Graphics::Player::Player(Math::Vector3f position) :
    Entity(position)
{
}

Graphics::Player::~Player()
{
}

void Graphics::Player::Move(float distance)
{
    this->increasePosition(
        std::sinf(glm::radians(this->_rotY)) * distance,
        0.0f,
        std::cosf(glm::radians(this->_rotY)) * distance
    );
}

void Graphics::Player::LookAt(Math::Vector2f target)
{
    this->_rotY = Math::LookAt(
        Math::Vector2f(this->_position.x, this->_position.z),
        target
    );
}

#pragma once

#include "../../Math/Vector.h"

namespace Graphics
{

    class HasPosition
    {
    public:
        HasPosition();
        HasPosition(Math::Vector3f position);
        Math::Vector3f getPosition() const;
        void setPosition(Math::Vector3f position);
        float getPositionX() const;
        void setPositionX(float x);
        void increasePositionX(float relativePositionX);
        float getPositionY() const;
        void setPositionY(float y);
        void increasePositionY(float relativePositionY);
        float getPositionZ() const;
        void setPositionZ(float z);
        void increasePositionZ(float relativePositionZ);
        void increasePosition(Math::Vector3f relativePosition);

    protected:
        Math::Vector3f _position;
    };


    inline Math::Vector3f HasPosition::getPosition() const
    {
        return this->_position;
    }

    inline void HasPosition::setPosition(Math::Vector3f position)
    {
        this->_position = position;
    }

    inline float HasPosition::getPositionX() const
    {
        return this->_position.x;
    }

    inline void HasPosition::setPositionX(float x)
    {
        this->_position.x = x;
    }

    inline void HasPosition::increasePositionX(float relativePositionX)
    {
        this->_position.x += relativePositionX;
    }

    inline float HasPosition::getPositionY() const
    {
        return this->_position.y;
    }

    inline void HasPosition::setPositionY(float y)
    {
        this->_position.y = y;
    }

    inline void HasPosition::increasePositionY(float relativePositionY)
    {
        this->_position.y += relativePositionY;
    }

    inline float HasPosition::getPositionZ() const
    {
        return this->_position.z;
    }

    inline void HasPosition::setPositionZ(float z)
    {
        this->_position.z = z;
    }

    inline void HasPosition::increasePositionZ(float relativePositionZ)
    {
        this->_position.z += relativePositionZ;
    }

    inline void HasPosition::increasePosition(Math::Vector3f relativePosition)
    {
        this->_position += relativePosition;
    }

}

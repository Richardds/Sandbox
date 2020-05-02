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
        float getPositionY() const;
        void setPositionY(float y);
        float getPositionZ() const;
        void setPositionZ(float z);
        void increasePosition(float x, float y, float z);
        void increasePosition(Math::Vector3f modifier);

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

}

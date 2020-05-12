#pragma once

namespace Graphics
{

    class HasRotation
    {
    public:
        HasRotation();
        HasRotation(float rotX, float rotY, float rotZ);

        float getRotationX() const;
        void setRotationX(float rotX);
        void increaseRotationX(float relativeRotX);
        void invertRotationX();
        float getRotationY() const;
        void setRotationY(float rotY);
        void increaseRotationY(float relativeRotY);
        void invertRotationY();
        float getRotationZ() const;
        void setRotationZ(float rotZ);
        void increaseRotationZ(float relativeRotZ);
        void invertRotationZ();
        void increaseRotation(float rotX, float rotY, float rotZ);

    protected:
        float _rotX;
        float _rotY;
        float _rotZ;
    };

    inline float HasRotation::getRotationX() const
    {
        return this->_rotX;
    }

    inline void HasRotation::setRotationX(float rotX)
    {
        this->_rotX = rotX;
    }

    inline void HasRotation::increaseRotationX(float relativeRotX)
    {
        this->_rotX += relativeRotX;
    }

    inline void HasRotation::invertRotationX()
    {
        this->_rotX = -this->_rotX;
    }

    inline float HasRotation::getRotationY() const
    {
        return this->_rotY;
    }

    inline void HasRotation::setRotationY(float rotY)
    {
        this->_rotY = rotY;
    }

    inline void HasRotation::increaseRotationY(float relativeRotY)
    {
        this->_rotY += relativeRotY;
    }

    inline void HasRotation::invertRotationY()
    {
        this->_rotY = -this->_rotY;
    }

    inline float HasRotation::getRotationZ() const
    {
        return this->_rotZ;
    }

    inline void HasRotation::setRotationZ(float rotZ)
    {
        this->_rotZ = rotZ;
    }

    inline void HasRotation::increaseRotationZ(float relativeRotZ)
    {
        this->_rotZ += relativeRotZ;
    }

    inline void HasRotation::invertRotationZ()
    {
        this->_rotZ = -this->_rotZ;
    }

    inline void HasRotation::increaseRotation(float rotX, float rotY, float rotZ)
    {
        this->_rotX += rotX;
        this->_rotY += rotY;
        this->_rotZ += rotZ;
    }

}

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
        float getRotationY() const;
        void setRotationY(float rotY);
        float getRotationZ() const;
        void setRotationZ(float rotZ);
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

    inline float HasRotation::getRotationY() const
    {
        return this->_rotY;
    }

    inline void HasRotation::setRotationY(float rotY)
    {
        this->_rotY = rotY;
    }

    inline float HasRotation::getRotationZ() const
    {
        return this->_rotZ;
    }

    inline void HasRotation::setRotationZ(float rotZ)
    {
        this->_rotZ = rotZ;
    }

}

#pragma once

namespace Graphics
{

    class HasScale
    {
    public:
        HasScale();
        HasScale(float scale);

        float getScale() const;
        void setScale(float scale);
        void increaseScale(float scale);

    protected:
        float _scale;
    };

    inline float HasScale::getScale() const
    {
        return this->_scale;
    }

    inline void HasScale::setScale(float scale)
    {
        this->_scale = scale;
    }

}

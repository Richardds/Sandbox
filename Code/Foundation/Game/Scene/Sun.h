#pragma once

#include "DirectionalLight.h"

namespace Graphics
{

    class Sun : public DirectionalLight
    {
    public:
        Sun();
        virtual ~Sun();
        float GetIntensity() const;
        void SetInstensity(float intensity);

    private:
        float _intensity;
    };

    inline float Graphics::Sun::GetIntensity() const
    {
        return this->_intensity;
    }

    inline void Sun::SetInstensity(float intensity)
    {
        this->_intensity = intensity;
    }

}

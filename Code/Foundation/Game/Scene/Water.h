#pragma once

#include <memory>

#include "../Attributes/HasPosition.h"
#include "../../Graphics/Mesh.h"
#include "../../Graphics/Texture.h"
#include "../../Graphics/Shaders/WaterShader.h"

namespace Graphics
{

    class Water : public HasPosition
    {
    public:
        Water();
        virtual ~Water();
        std::shared_ptr<Mesh> GetMesh() const;
        void SetMesh(std::shared_ptr<Mesh> mesh);
        std::shared_ptr<Texture> GetDistortionMap() const;
        bool HasDistortionMap() const;
        void SetDistortionMap(std::shared_ptr<Texture> texture);
        float GetDistortionSpeed() const;
        void SetDistortionSpeed(float speed);
        void Update(float delta);
        void Render(std::shared_ptr<WaterShader> shader);

    private:
        static constexpr float DEFAULT_DISTORTION_SPEED = 0.025f;

        std::shared_ptr<Mesh> _mesh;
        std::shared_ptr<Texture> _distortionMap;
        float _distortionOffset;
        float _distortionSpeed;
    };

    inline std::shared_ptr<Mesh> Graphics::Water::GetMesh() const
    {
        return this->_mesh;
    }

    inline void Graphics::Water::SetMesh(std::shared_ptr<Mesh> mesh)
    {
        this->_mesh = mesh;
    }

    inline std::shared_ptr<Texture> Water::GetDistortionMap() const
    {
        return this->_distortionMap;
    }

    inline bool Water::HasDistortionMap() const
    {
        return static_cast<bool>(this->_distortionMap);
    }

    inline void Water::SetDistortionMap(std::shared_ptr<Texture> texture)
    {
        _assert(texture);
        _assert(Texture::State::LOADED == texture->GetState());
        this->_distortionMap = texture;
    }

    inline float Water::GetDistortionSpeed() const
    {
        return this->_distortionSpeed;
    }

    inline void Water::SetDistortionSpeed(float speed)
    {
        this->_distortionSpeed = speed;
    }

}

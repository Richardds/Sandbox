#pragma once

#include <memory>

#include "../Attributes/HasPosition.h"
#include "../../Graphics/TexturedMesh.h"
#include "../../Graphics/Shaders/WaterShader.h"

namespace Graphics
{

    class Water : public HasPosition
    {
    public:
        Water();
        virtual ~Water();
        std::shared_ptr<TexturedMesh> GetMesh() const;
        void SetMesh(std::shared_ptr<TexturedMesh> mesh);
        float GetDistortionSpeed() const;
        void SetDistortionSpeed(float speed);
        float GetTiling() const;
        void SetTiling(float tiling);
        void Update(float delta);
        void Render(std::shared_ptr<WaterShader> shader);

    private:
        static constexpr float DEFAULT_DISTORTION_SPEED = 0.025f;
        static constexpr float DEFAULT_TILING = 1.0f;

        std::shared_ptr<TexturedMesh> _mesh;
        float _distortionOffset;
        float _distortionSpeed;
        float _tiling;
    };

    inline std::shared_ptr<TexturedMesh> Graphics::Water::GetMesh() const
    {
        return this->_mesh;
    }

    inline void Graphics::Water::SetMesh(std::shared_ptr<TexturedMesh> mesh)
    {
        this->_mesh = mesh;
    }

    inline float Water::GetDistortionSpeed() const
    {
        return this->_distortionSpeed;
    }

    inline void Water::SetDistortionSpeed(float speed)
    {
        this->_distortionSpeed = speed;
    }

    inline float Water::GetTiling() const
    {
        return this->_tiling;
    }

    inline void Water::SetTiling(float tiling)
    {
        this->_tiling = tiling;
    }

}

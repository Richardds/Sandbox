// ----------------------------------------------------------------------------------------
//  \file       Water.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Graphics/TexturedMesh.h"
#include "Graphics/Shaders/WaterShader.h"
#include "Game/Attributes/HasPosition3D.h"

namespace Graphics
{
    /// Water entity
    class EXPORT Water : public HasPosition3D
    {
    public:
        Water();

        std::shared_ptr<TexturedMesh> GetMesh() const;
        void SetMesh(const std::shared_ptr<TexturedMesh>& mesh);
        float GetDistortionSpeed() const;
        void SetDistortionSpeed(float speed);
        float GetTiling() const;
        void SetTiling(float tiling);
        bool GetWavesEnabled() const;
        void SetWavesEnabled(bool wavesEnabled);
        void Update(float delta);
        void Render(const std::shared_ptr<WaterShader>& shader) const;

    private:
        /// Speed of distortion texture offset motion when unspecified
        static constexpr float DEFAULT_DISTORTION_SPEED = 0.025f;
        /// Distortion texture tiling when unspecified
        static constexpr float DEFAULT_TILING = 1.0f;

        std::shared_ptr<TexturedMesh> _mesh;
        float _distortionOffset;
        float _distortionSpeed;
        float _tiling;
        bool _wavesEnabled;
    };

    inline std::shared_ptr<TexturedMesh> Water::GetMesh() const
    {
        return this->_mesh;
    }

    inline void Water::SetMesh(const std::shared_ptr<TexturedMesh>& mesh)
    {
        this->_mesh = mesh;
    }

    inline float Water::GetDistortionSpeed() const
    {
        return this->_distortionSpeed;
    }

    inline void Water::SetDistortionSpeed(const float speed)
    {
        this->_distortionSpeed = speed;
    }

    inline float Water::GetTiling() const
    {
        return this->_tiling;
    }

    inline void Water::SetTiling(const float tiling)
    {
        this->_tiling = tiling;
    }

    inline bool Water::GetWavesEnabled() const
    {
        return this->_wavesEnabled;
    }

    inline void Water::SetWavesEnabled(const bool wavesEnabled)
    {
        this->_wavesEnabled = wavesEnabled;
    }
}

// ----------------------------------------------------------------------------------------
//  \file       HasRotation.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"

namespace Graphics
{
	/// Provides 3D rotation attributes and operations
	class HasRotation
	{
	public:
		HasRotation();
		HasRotation(float rotationX, float rotationY, float rotationZ);
		virtual ~HasRotation() = default;

		[[nodiscard]] float GetRotationX() const;
		void SetRotationX(float rotationX);
		void IncreaseRotationX(float relativeRotationX);
		void InvertRotationX();
		[[nodiscard]] float GetRotationY() const;
		void SetRotationY(float rotationY);
		void IncreaseRotationY(float relativeRotationY);
		void InvertRotationY();
		[[nodiscard]] float GetRotationZ() const;
		void SetRotationZ(float rotationZ);
		void IncreaseRotationZ(float relativeRotationZ);
		void InvertRotationZ();
		void IncreaseRotation(float rotationX, float rotationY, float rotationZ);

	protected:
		float _rotationX;
		float _rotationY;
		float _rotationZ;
	};

	inline float HasRotation::GetRotationX() const
	{
		return this->_rotationX;
	}

	inline void HasRotation::SetRotationX(const float rotationX)
	{
		this->_rotationX = rotationX;
	}

	inline void HasRotation::IncreaseRotationX(const float relativeRotationX)
	{
		this->_rotationX += relativeRotationX;
	}

	inline void HasRotation::InvertRotationX()
	{
		this->_rotationX = -this->_rotationX;
	}

	inline float HasRotation::GetRotationY() const
	{
		return this->_rotationY;
	}

	inline void HasRotation::SetRotationY(const float rotationY)
	{
		this->_rotationY = rotationY;
	}

	inline void HasRotation::IncreaseRotationY(const float relativeRotationY)
	{
		this->_rotationY += relativeRotationY;
	}

	inline void HasRotation::InvertRotationY()
	{
		this->_rotationY = -this->_rotationY;
	}

	inline float HasRotation::GetRotationZ() const
	{
		return this->_rotationZ;
	}

	inline void HasRotation::SetRotationZ(const float rotationZ)
	{
		this->_rotationZ = rotationZ;
	}

	inline void HasRotation::IncreaseRotationZ(const float relativeRotationZ)
	{
		this->_rotationZ += relativeRotationZ;
	}

	inline void HasRotation::InvertRotationZ()
	{
		this->_rotationZ = -this->_rotationZ;
	}

	inline void HasRotation::IncreaseRotation(const float rotationX, const float rotationY, const float rotationZ)
	{
		this->_rotationX += rotationX;
		this->_rotationY += rotationY;
		this->_rotationZ += rotationZ;
	}
}

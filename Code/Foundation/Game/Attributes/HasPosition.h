// ----------------------------------------------------------------------------------------
//  \file       HasPosition.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Math/Vector.h"

namespace Graphics
{
	/// Provides 3D position attributes and operations
	class HasPosition
	{
	public:
		HasPosition();
		virtual ~HasPosition() = default;
		explicit HasPosition(const Math::Vector3f& position);
		[[nodiscard]] Math::Vector3f GetPosition() const;
		void SetPosition(const Math::Vector3f& position);
		[[nodiscard]] float GetPositionX() const;
		void SetPositionX(float positionX);
		void IncreasePositionX(float relativePositionX);
		[[nodiscard]] float GetPositionY() const;
		void SetPositionY(float positionY);
		void IncreasePositionY(float relativePositionY);
		[[nodiscard]] float GetPositionZ() const;
		void SetPositionZ(float positionZ);
		void IncreasePositionZ(float relativePositionZ);
		void IncreasePosition(const Math::Vector3f& relativePosition);

	protected:
		Math::Vector3f _position;
	};

	inline Math::Vector3f HasPosition::GetPosition() const
	{
		return this->_position;
	}

	inline void HasPosition::SetPosition(const Math::Vector3f& position)
	{
		this->_position = position;
	}

	inline float HasPosition::GetPositionX() const
	{
		return this->_position.x;
	}

	inline void HasPosition::SetPositionX(const float positionX)
	{
		this->_position.x = positionX;
	}

	inline void HasPosition::IncreasePositionX(const float relativePositionX)
	{
		this->_position.x += relativePositionX;
	}

	inline float HasPosition::GetPositionY() const
	{
		return this->_position.y;
	}

	inline void HasPosition::SetPositionY(const float positionY)
	{
		this->_position.y = positionY;
	}

	inline void HasPosition::IncreasePositionY(const float relativePositionY)
	{
		this->_position.y += relativePositionY;
	}

	inline float HasPosition::GetPositionZ() const
	{
		return this->_position.z;
	}

	inline void HasPosition::SetPositionZ(const float positionZ)
	{
		this->_position.z = positionZ;
	}

	inline void HasPosition::IncreasePositionZ(const float relativePositionZ)
	{
		this->_position.z += relativePositionZ;
	}

	inline void HasPosition::IncreasePosition(const Math::Vector3f& relativePosition)
	{
		this->_position += relativePosition;
	}
}

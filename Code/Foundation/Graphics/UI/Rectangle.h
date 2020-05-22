#pragma once

#include "Precompiled.h"
#include "Math/Vector.h"

namespace Graphics
{
	class Rectangle
	{
	public:
		Rectangle(float width, float height, const Math::Vector3f& color);
		void Render();
		void SetWidth(float width);
		[[nodiscard]] float GetWidth() const;
		void SetHeight(float height);
		[[nodiscard]] float GetHeight() const;
		void SetColor(const Math::Vector3f& color);
		[[nodiscard]] Math::Vector3f GetColor() const;

	private:
		float _width;
		float _height;
		Math::Vector3f _color;
	};

	inline void Rectangle::SetWidth(const float width)
	{
		this->_width = width;
	}

	inline float Rectangle::GetWidth() const
	{
		return this->_width;
	}

	inline void Rectangle::SetHeight(const float height)
	{
		this->_height = height;
	}

	inline float Rectangle::GetHeight() const
	{
		return this->_height;
	}

	inline void Rectangle::SetColor(const Math::Vector3f& color)
	{
		this->_color = color;
	}

	inline Math::Vector3f Rectangle::GetColor() const
	{
		return this->_color;
	}
}

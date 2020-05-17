#pragma once

#include "Light.h"
#include "../Attributes/HasPosition.h"

namespace Graphics
{
	class PointLight : public Light, public HasPosition
	{
	public:
		PointLight();

		[[nodiscard]] Math::Vector3f GetAttenuation() const;
		void SetAttenuation(const Math::Vector3f& attenuation);

	private:
		Math::Vector3f _attenuation;
	};

	inline Math::Vector3f PointLight::GetAttenuation() const
	{
		return this->_attenuation;
	}

	inline void PointLight::SetAttenuation(const Math::Vector3f& attenuation)
	{
		this->_attenuation = attenuation;
	}
}

#pragma once

#include "../Attributes/HasPosition.h"
#include "../Attributes/HasRotation.h"

namespace Graphics
{
	class Camera : public HasPosition, public HasRotation
	{
	public:
		Camera();
		virtual ~Camera() = default;

		explicit Camera(float fieldOfView);
		[[nodiscard]] float GetFieldOfView() const;
		void SetFieldOfView(float fieldOfView);
		void LookAt(Math::Vector3f target);

	private:
		float _fieldOfView;
	};

	inline float Camera::GetFieldOfView() const
	{
		return this->_fieldOfView;
	}

	inline void Camera::SetFieldOfView(const float fieldOfView)
	{
		this->_fieldOfView = fieldOfView;
	}
}

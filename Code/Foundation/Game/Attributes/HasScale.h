#pragma once

namespace Graphics
{
	class HasScale
	{
	public:
		HasScale();
		explicit HasScale(float scale);
		virtual ~HasScale() = default;

		[[nodiscard]] float GetScale() const;
		void SetScale(float scale);
		void IncreaseScale(float scale);

	protected:
		float _scale;
	};

	inline float HasScale::GetScale() const
	{
		return this->_scale;
	}

	inline void HasScale::SetScale(const float scale)
	{
		this->_scale = scale;
	}
}

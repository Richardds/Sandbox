#pragma once

#include "../../Graphics/Model.h"
#include "../../Graphics/Shaders/EntityShader.h"
#include "../Attributes/HasPosition.h"
#include "../Attributes/HasRotation.h"
#include "../Attributes/HasScale.h"

namespace Graphics
{
	class Entity : public HasPosition, public HasRotation, public HasScale
	{
	public:
		Entity();
		virtual ~Entity() = default;

		explicit Entity(const Math::Vector3f& position, float rotX = 0.0f, float rotY = 0.0f, float rotZ = 0.0f);
		[[nodiscard]] std::shared_ptr<Model> GetModel() const;
		void SetModel(const std::shared_ptr<Model>& model);
		void Render(const std::shared_ptr<EntityShader>& shader) const;

	private:
		std::shared_ptr<Model> _model;
	};

	inline std::shared_ptr<Model> Entity::GetModel() const
	{
		return this->_model;
	}

	inline void Entity::SetModel(const std::shared_ptr<Model>& model)
	{
		this->_model = model;
	}
}

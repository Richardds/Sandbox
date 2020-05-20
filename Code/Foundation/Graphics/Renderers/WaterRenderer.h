#pragma once

#include <functional>

#include "../FrameBuffer.h"
#include "../Texture.h"
#include "../../Game/Scene/DirectionalLight.h"
#include "../../Game/Scene/Water.h"
#include "../Shaders/WaterShader.h"

namespace Graphics
{
	class WaterRenderer
	{
	public:
		enum class State
		{
			Initial,
			Ready
		};

		const unsigned int TEXTURE_SIZE = 2048;

		WaterRenderer();
		bool Setup(const std::shared_ptr<const Projection>& projection);
		void Begin(const std::shared_ptr<Camera>& camera, const std::shared_ptr<DirectionalLight>& sun) const;
		void RenderToReflectionBuffer(const std::function<void()>& renderFunction) const;
		void RenderToRefractionBuffer(const std::function<void()>& renderFunction) const;
		void Render(const std::shared_ptr<Water>& water) const;

	private:
		State _state;
		std::shared_ptr<WaterShader> _shader;

		std::shared_ptr<FrameBuffer> _reflectionFrameBuffer;
		std::shared_ptr<Texture> _reflectionTexture;
		std::shared_ptr<FrameBuffer> _refractionFrameBuffer;
		std::shared_ptr<Texture> _refractionTexture;
	};
}

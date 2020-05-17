#pragma once

#include <functional>

#include "../FrameBuffer.h"
#include "../Mesh.h"
#include "../Texture.h"
#include "../Shaders/HUDShader.h"

namespace Graphics
{
	class HUDRenderer
	{
	public:
		enum class State
		{
			Initial,
			Ready
		};

		const unsigned int TEXTURE_SIZE = 512;

		HUDRenderer();
		bool Setup(const std::shared_ptr<const Projection>& projection);
		void Begin() const;
		void RenderToMapBuffer(const std::function<void()>& renderFunction) const;
		void Render(const Math::Vector2f& screenPosition) const;

	private:
		State _state;
		std::shared_ptr<HUDShader> _shader;
		std::shared_ptr<Mesh> _mapMesh;
		std::shared_ptr<FrameBuffer> _mapFrameBuffer;
		std::shared_ptr<Texture> _mapTexture;
	};
}

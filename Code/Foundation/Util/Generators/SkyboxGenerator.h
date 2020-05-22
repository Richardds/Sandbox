#pragma once

#include "Precompiled.h"
#include "Core/Singleton.h"
#include "Util/Generators/Generator.h"

namespace Util
{
	class SkyboxGenerator : public Generator
	{
	_Singleton(SkyboxGenerator)

	public:
		SkyboxGenerator();
		std::shared_ptr<Graphics::Mesh> Generate(float size);

	private:
		Graphics::VertexAttributeConfig _skyboxAttributesTemplate;
	};
}

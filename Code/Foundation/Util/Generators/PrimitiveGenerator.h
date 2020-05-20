#pragma once

#include "Generator.h"
#include "../../Core/Singleton.h"

namespace Util
{
	class PrimitiveGenerator : public Generator
	{
	_Singleton(PrimitiveGenerator)

	public:
		PrimitiveGenerator();
		std::shared_ptr<Graphics::Mesh> Generate2dQuad(float size);
		std::shared_ptr<Graphics::Mesh> Generate3dQuad(float size);
		
	private:
		Graphics::VertexAttributeConfig _2dQuadAttributesTemplate;
		Graphics::VertexAttributeConfig _3dQuadAttributesTemplate;
	};
}

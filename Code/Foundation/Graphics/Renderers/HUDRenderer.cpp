#include "HUDRenderer.h"
#include "../../IO/Console.h"
#include "../../Math/Utils.h"
#include "../../Util/Generators/PrimitiveGenerator.h"

Graphics::HUDRenderer::HUDRenderer() :
	_state(State::Initial)
{
}

bool Graphics::HUDRenderer::Setup(const std::shared_ptr<const Projection>& projection)
{
	_Assert(State::Initial == this->_state);

	// Setup water shader
	this->_shader = std::make_shared<HUDShader>();
	if (!this->_shader->Setup())
	{
		IO::Console::Instance().Error("Failed to load water shader\n");
		return false;
	}

	// Generate basic quad for map texture rendering
	this->_mapMesh = Util::PrimitiveGenerator::Instance().Generate3dQuad(0.4f);

	this->_shader->Use();
	this->_shader->LoadAspectRatio(projection->GetAspectRatio());

	this->_mapFrameBuffer = std::make_shared<FrameBuffer>();
	this->_mapFrameBuffer->Bind();
	this->_mapTexture = std::make_shared<Texture>(GL_TEXTURE_2D);
	this->_mapTexture->Bind();
	this->_mapTexture->Data(this->_mapFrameBuffer, TEXTURE_SIZE, TEXTURE_SIZE);
	this->_mapTexture->Unbind();
	this->_mapFrameBuffer->Unbind();

	this->_state = State::Ready;

	return true;
}

void Graphics::HUDRenderer::Begin(const Math::Vector3f& position, float height) const
{
	this->_shader->Use();
	this->_mapTexture->Activate(Texture::Bank::Diffuse);

	// TODO
}

void Graphics::HUDRenderer::RenderToMapBuffer(const std::function<void()>& renderFunction) const
{
	this->_mapFrameBuffer->Activate(TEXTURE_SIZE, TEXTURE_SIZE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderFunction();
	this->_mapFrameBuffer->Deactivate();
}

void Graphics::HUDRenderer::Render(const Math::Vector2f& screenPosition) const
{
	_Assert(State::Ready == this->_state);

	this->_shader->LoadPosition(screenPosition);

	this->_mapMesh->DrawElements();
}

#include "WaterRenderer.h"
#include "../../Math/Utils.h"
#include "../../IO/Console.h"

Graphics::WaterRenderer::WaterRenderer() :
	_state(State::INITIAL)
{
}

Graphics::WaterRenderer::~WaterRenderer()
{
}

bool Graphics::WaterRenderer::Setup(std::shared_ptr<const Projection> projection)
{
	_assert(State::INITIAL == this->_state);

	// Setup water shader
	this->_shader = std::make_shared<WaterShader>();
	if (!this->_shader->Setup()) {
		IO::Console::Instance().Error("Failed to load water shader\n");
		return false;
	}

	this->_shader->Use();
	this->_shader->LoadProjection(projection);

	this->_reflectionFrameBuffer = std::make_shared<Graphics::FrameBuffer>(GL_COLOR_ATTACHMENT0);
	this->_reflectionFrameBuffer->Bind();
	this->_reflectionTexture = std::make_shared<Texture>();
	this->_reflectionTexture->Bind();
	this->_reflectionTexture->Data(this->_reflectionFrameBuffer, WaterRenderer::TEXTURE_SIZE, WaterRenderer::TEXTURE_SIZE);
	this->_reflectionTexture->Unbind();
	//this->_reflectionRenderBuffer = std::make_shared<RenderBuffer>(GL_DEPTH_COMPONENT, WaterRenderer::TEXTURE_SIZE, WaterRenderer::TEXTURE_SIZE);
	this->_reflectionFrameBuffer->Unbind();

	this->_refractionFrameBuffer = std::make_shared<Graphics::FrameBuffer>(GL_COLOR_ATTACHMENT0);
	this->_refractionFrameBuffer->Bind();
	this->_refractionTexture = std::make_shared<Texture>();
	this->_refractionTexture->Bind();
	this->_refractionTexture->Data(this->_refractionFrameBuffer, WaterRenderer::TEXTURE_SIZE, WaterRenderer::TEXTURE_SIZE);
	this->_refractionTexture->Unbind();
	//this->_refractionRenderBuffer = std::make_shared<RenderBuffer>(GL_DEPTH_COMPONENT, WaterRenderer::TEXTURE_SIZE, WaterRenderer::TEXTURE_SIZE);
	this->_refractionFrameBuffer->Unbind();

	this->_state = State::READY;

	return true;
}

void Graphics::WaterRenderer::Begin(std::shared_ptr<Camera> camera, std::shared_ptr<Sun> sun)
{
	this->_shader->Use();
	this->_shader->LoadView(camera);
	this->_shader->LoadSun(sun);
}

void Graphics::WaterRenderer::Render(std::shared_ptr<Water> water)
{
	_assert(State::READY == this->_state);

	this->_shader->LoadWorldTransformation(Math::TranslationMatrix(water->getPosition()));
	water->GetMesh()->DrawElements();
}

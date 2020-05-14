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

	// Reflection
	this->_reflectionFrameBuffer = std::make_shared<Graphics::FrameBuffer>();
	this->_reflectionFrameBuffer->Bind();
	this->_reflectionTexture = std::make_shared<Texture>(GL_TEXTURE_2D);
	this->_reflectionTexture->Bind();
	this->_reflectionTexture->Data(this->_reflectionFrameBuffer, WaterRenderer::TEXTURE_SIZE, WaterRenderer::TEXTURE_SIZE);
	this->_reflectionTexture->Unbind();
	this->_reflectionFrameBuffer->Unbind();

	// Refraction
	this->_refractionFrameBuffer = std::make_shared<Graphics::FrameBuffer>();
	this->_refractionFrameBuffer->Bind();
	this->_refractionTexture = std::make_shared<Texture>(GL_TEXTURE_2D);
	this->_refractionTexture->Bind();
	this->_refractionTexture->Data(this->_refractionFrameBuffer, WaterRenderer::TEXTURE_SIZE, WaterRenderer::TEXTURE_SIZE);
	this->_refractionTexture->Unbind();
	this->_refractionFrameBuffer->Unbind();

	this->_state = State::READY;

	return true;
}

void Graphics::WaterRenderer::Begin(std::shared_ptr<Camera> camera, std::shared_ptr<DirectionalLight> sun)
{
	this->_shader->Use();
	this->_shader->LoadCamera(camera);
	this->_shader->LoadSun(sun);

	this->_reflectionTexture->Activate(Texture::Bank::REFLECTION);
	this->_refractionTexture->Activate(Texture::Bank::REFRACTION);
}

void Graphics::WaterRenderer::RenderToReflectionBuffer(const std::function<void()>& renderFunction)
{
	this->_reflectionFrameBuffer->Activate(WaterRenderer::TEXTURE_SIZE, WaterRenderer::TEXTURE_SIZE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderFunction();
	this->_reflectionFrameBuffer->Deactivate();
}

void Graphics::WaterRenderer::RenderToRefractionBuffer(const std::function<void()>& renderFunction)
{
	this->_refractionFrameBuffer->Activate(WaterRenderer::TEXTURE_SIZE, WaterRenderer::TEXTURE_SIZE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderFunction();
	this->_refractionFrameBuffer->Deactivate();
}

void Graphics::WaterRenderer::Render(std::shared_ptr<Water> water)
{
	_assert(State::READY == this->_state);

	water->Render(this->_shader);
}

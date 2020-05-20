#include "WaterRenderer.h"
#include "../../IO/Console.h"

Graphics::WaterRenderer::WaterRenderer() :
	_state(State::Initial)
{
}

bool Graphics::WaterRenderer::Setup(const std::shared_ptr<const Projection>& projection)
{
	_Assert(State::Initial == this->_state);

	// Setup water shader
	this->_shader = std::make_shared<WaterShader>();
	if (!this->_shader->Setup())
	{
		IO::Console::Instance().Error("Failed to load water shader\n");
		return false;
	}

	this->_shader->Use();
	this->_shader->LoadProjection(projection);

	// Reflection
	this->_reflectionFrameBuffer = std::make_shared<FrameBuffer>();
	this->_reflectionFrameBuffer->Bind();
	this->_reflectionTexture = std::make_shared<Texture>();
	this->_reflectionTexture->SetTarget(GL_TEXTURE_2D);
	this->_reflectionTexture->Bind();
	this->_reflectionTexture->Data(this->_reflectionFrameBuffer, TEXTURE_SIZE, TEXTURE_SIZE);
	this->_reflectionTexture->Unbind();
	this->_reflectionFrameBuffer->Unbind();

	// Refraction
	this->_refractionFrameBuffer = std::make_shared<FrameBuffer>();
	this->_refractionFrameBuffer->Bind();
	
	this->_refractionTexture = std::make_shared<Texture>();
	this->_refractionTexture->SetTarget(GL_TEXTURE_2D);
	this->_refractionTexture->Bind();
	this->_refractionTexture->Data(this->_refractionFrameBuffer, TEXTURE_SIZE, TEXTURE_SIZE);
	this->_refractionTexture->Unbind();
	
	this->_refractionFrameBuffer->Unbind();

	this->_state = State::Ready;

	return true;
}

void Graphics::WaterRenderer::Begin(const std::shared_ptr<Camera>& camera,
                                    const std::shared_ptr<DirectionalLight>& sun) const
{
	this->_shader->Use();
	this->_shader->LoadCamera(camera);
	this->_shader->LoadSun(sun);

	this->_reflectionTexture->Activate(Texture::Bank::Reflection);
	this->_refractionTexture->Activate(Texture::Bank::Refraction);
}

void Graphics::WaterRenderer::RenderToReflectionBuffer(const std::function<void()>& renderFunction) const
{
	this->_reflectionFrameBuffer->Activate(TEXTURE_SIZE, TEXTURE_SIZE);
	this->_reflectionFrameBuffer->Clear();
	renderFunction();
	this->_reflectionFrameBuffer->Deactivate();
}

void Graphics::WaterRenderer::RenderToRefractionBuffer(const std::function<void()>& renderFunction) const
{
	this->_refractionFrameBuffer->Activate(TEXTURE_SIZE, TEXTURE_SIZE);
	this->_refractionFrameBuffer->Clear();
	renderFunction();
	this->_refractionFrameBuffer->Deactivate();
}

void Graphics::WaterRenderer::Render(const std::shared_ptr<Water>& water) const
{
	_Assert(water);
	_Assert(State::Ready == this->_state);

	water->Render(this->_shader);
}

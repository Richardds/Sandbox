// ----------------------------------------------------------------------------------------
//  \file       WaterRenderer.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Renderers/WaterRenderer.h"
#include "IO/Console.h"

bool Graphics::WaterRenderer::Setup(const std::shared_ptr<const Projection>& projection)
{
    _Assert(State::Initial == this->GetState());

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
    this->_reflectionTexture = std::make_shared<Texture>();
    this->_reflectionTexture->SetTarget(GL_TEXTURE_2D);
    this->_reflectionTexture->Bind();
    this->_reflectionDepthBuffer = std::make_shared<RenderBuffer>();
    this->_reflectionDepthBuffer->Bind();
    this->_reflectionDepthBuffer->Storage(GL_DEPTH_COMPONENT, TEXTURE_SIZE, TEXTURE_SIZE);
    this->_reflectionFrameBuffer = std::make_shared<FrameBuffer>();
    this->_reflectionFrameBuffer->Bind();
    this->_reflectionFrameBuffer->AttachTexture(this->_reflectionTexture, TEXTURE_SIZE, TEXTURE_SIZE);
    this->_reflectionFrameBuffer->AttachDepthBuffer(this->_reflectionDepthBuffer);
    this->_reflectionFrameBuffer->Unbind();
    this->_reflectionTexture->Unbind();
    this->_reflectionDepthBuffer->Unbind();

    // Refraction
    this->_refractionTexture = std::make_shared<Texture>();
    this->_refractionTexture->SetTarget(GL_TEXTURE_2D);
    this->_refractionTexture->Bind();
    this->_refractionDepthBuffer = std::make_shared<RenderBuffer>();
    this->_refractionDepthBuffer->Bind();
    this->_refractionDepthBuffer->Storage(GL_DEPTH_COMPONENT, TEXTURE_SIZE, TEXTURE_SIZE);
    this->_refractionFrameBuffer = std::make_shared<FrameBuffer>();
    this->_refractionFrameBuffer->Bind();
    this->_refractionFrameBuffer->AttachTexture(this->_refractionTexture, TEXTURE_SIZE, TEXTURE_SIZE);
    this->_refractionFrameBuffer->AttachDepthBuffer(this->_refractionDepthBuffer);
    this->_refractionFrameBuffer->Unbind();
    this->_refractionTexture->Unbind();
    this->_refractionDepthBuffer->Unbind();

    this->FinishLoading();

    return true;
}

void Graphics::WaterRenderer::Begin(const std::shared_ptr<Camera>& camera,
                                    const std::shared_ptr<DirectionalLight>& sun,
                                    const std::unordered_map<std::string, std::shared_ptr<PointLight>>& lights,
                                    const std::shared_ptr<SpotLight>& flashLight) const
{
    this->_shader->Use();
    this->_shader->LoadCamera(camera);
    this->_shader->LoadSun(sun);
    this->_shader->LoadLights(lights);

    flashLight->SetPosition(camera->GetPosition());
    flashLight->SetDirection(camera->GetDirection());
    this->_shader->LoadFlashLight(flashLight);

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
    _Assert(State::Ready == this->GetState());

    water->Render(this->_shader);
}

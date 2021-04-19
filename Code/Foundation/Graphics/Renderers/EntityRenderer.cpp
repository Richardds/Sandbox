// ----------------------------------------------------------------------------------------
//  \file       EntityRenderer.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Graphics/Renderers/EntityRenderer.h"
#include "IO/Console.h"

bool Graphics::EntityRenderer::Setup(const std::shared_ptr<const Projection>& projection)
{
    _Assert(State::Initial == this->GetState())

    // Setup entity shader
    this->_shader = std::make_shared<EntityShader>();
    if (!this->_shader->Setup())
    {
        IO::Console::Instance().Error("Failed to load entity shader\n");
        return false;
    }

    this->_shader->Use();
    this->_shader->LoadProjection(projection);

    this->FinishLoading();

    return true;
}

void Graphics::EntityRenderer::Begin(const std::shared_ptr<Camera>& camera,
                                     const std::shared_ptr<DirectionalLight>& sun,
                                     const std::shared_ptr<Skybox>& skybox,
                                     const std::vector<std::shared_ptr<PointLight>>& lights,
                                     const std::shared_ptr<SpotLight>& flashLight) const
{
    this->_shader->Use();
    this->_shader->LoadCamera(camera);
    this->_shader->LoadSun(sun);
    this->_shader->LoadLights(lights);

    flashLight->SetPosition(camera->GetPosition());
    flashLight->SetDirection(camera->GetDirection());
    this->_shader->LoadFlashLight(flashLight);

    if (skybox == nullptr)
    {
        this->_shader->LoadHasSkyboxMap(false);
    } else
    {
        this->_shader->LoadHasSkyboxMap(true);
        skybox->GetTexture()->Activate(Texture::Bank::Skybox);
    }
}

void Graphics::EntityRenderer::Render(const std::shared_ptr<Entity>& entity) const
{
    _Assert(entity)
    _Assert(State::Ready == this->GetState())

    entity->Render(this->_shader);
}

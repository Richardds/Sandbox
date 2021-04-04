// ----------------------------------------------------------------------------------------
//  \file       TextRenderer.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Renderers/TextRenderer.h"
#include "Graphics/GraphicsUtils.h"
#include "IO/Console.h"
#include "Util/ResourcesLoader.h"
#include "Util/Generators/TextMeshGenerator.h"

bool Graphics::TextRenderer::Setup()
{
    _Assert(State::Initial == this->GetState());

    // Setup glyph shader
    this->_shader = std::make_shared<TextShader>();
    if (!this->_shader->Setup())
    {
        IO::Console::Instance().Error("Failed to load glyph shader\n");
        return false;
    }
    
    this->_shader->Use();
    this->_shader->LoadScreenResolution(Core::Instance().GetResolution());

    this->FinishLoading();

    return true;
}

void Graphics::TextRenderer::Begin() const
{
    this->_shader->Use();
}

void Graphics::TextRenderer::Render(const std::shared_ptr<Text>& text) const
{
    _Assert(State::Ready == this->GetState());

    text->Render(this->_shader);
}

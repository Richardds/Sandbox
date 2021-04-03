// ----------------------------------------------------------------------------------------
//  \file       GlyphRenderer.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Renderers/GlyphRenderer.h"
#include "IO/Console.h"
#include "Util/ResourcesLoader.h"
#include "Util/Generators/PrimitiveGenerator.h"

bool Graphics::GlyphRenderer::Setup()
{
    _Assert(State::Initial == this->GetState());

    // Setup glyph shader
    this->_shader = std::make_shared<GlyphShader>();
    if (!this->_shader->Setup())
    {
        IO::Console::Instance().Error("Failed to load glyph shader\n");
        return false;
    }

    // Generate glyph mesh
    this->_glyphMesh = Util::PrimitiveGenerator::Instance().Generate2dQuad(0.5f);

    this->_shader->Use();
    this->_shader->LoadScreenResolution(Core::Instance().GetResolution());

    this->FinishLoading();

    return true;
}

void Graphics::GlyphRenderer::SetFontType(const std::shared_ptr<FontType>& fontType)
{
    this->_fontType = fontType;
}

void Graphics::GlyphRenderer::Begin() const
{
    this->_shader->Use();
    this->_fontType->GetGlyphsMap()->Activate(Texture::Bank::Glyphs);
}

void Graphics::GlyphRenderer::Render(const char character, const float x, const float y) const
{
    _Assert(State::Ready == this->GetState());

    this->_glyphMesh->DrawElements();
}

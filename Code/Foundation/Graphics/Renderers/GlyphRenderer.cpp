// ----------------------------------------------------------------------------------------
//  \file       GlyphRenderer.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Graphics/Renderers/GlyphRenderer.h"
#include "Graphics/GraphicsUtils.h"
#include "IO/Console.h"
#include "Util/ResourcesLoader.h"
#include "Util/Generators/GlyphMeshGenerator.h"

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
    this->_glyphMesh = Util::GlyphMeshGenerator::Instance().Generate(128.0f, 128.0f, Math::Vector2f(0.0f));

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

// ----------------------------------------------------------------------------------------
//  \file       GlyphRenderer.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Graphics/Renderers/Renderer.h"
#include "Game/Scene/Object/Water.h"
#include "Graphics/FontType.h"
#include "Graphics/Shaders/GlyphShader.h"

namespace Graphics
{
    /// Renderer which renders glyphs
    class GlyphRenderer : public Renderer<GlyphShader>
    {
    public:
        GlyphRenderer() = default;

        bool Setup();
        void SetFontType(const std::shared_ptr<FontType>& fontType);
        void Begin() const;
        void Render(char character, float x, float y) const;

    private:
        std::shared_ptr<Mesh> _glyphMesh;
        std::shared_ptr<FontType> _fontType;
    };
}

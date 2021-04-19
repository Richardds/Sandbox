// ----------------------------------------------------------------------------------------
//  \file       TextRenderer.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"
#include "Graphics/Renderers/Renderer.h"
#include "Graphics/Text.h"
#include "Graphics/Shaders/TextShader.h"

namespace Graphics
{
    /// Renderer which renders text
    class EXPORT TextRenderer : public Renderer<TextShader>
    {
    public:
        TextRenderer() = default;

        bool Setup();
        void Begin() const;
        void Render(const std::shared_ptr<Text>& text) const;
    };
}

// ----------------------------------------------------------------------------------------
//  \file       DuckManager.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Game/Scene/Object/Duck.h"
#include "Graphics/Renderers/EntityRenderer.h"

namespace Sandbox
{
    /// Duck manager class for managing all ducks in the scene
    class DuckManager
    {
    public:
        DuckManager() = default;
        virtual ~DuckManager() = default;

        void Update(float delta);
        void Reset();
        void Manage(const std::shared_ptr<Duck>& duck);
        void RenderWith(const std::shared_ptr<Graphics::EntityRenderer>& renderer);

    private:
        std::list<std::shared_ptr<Duck>> _ducks;
    };
}

// ----------------------------------------------------------------------------------------
//  \file       DuckManager.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include <Graphics/Renderers/EntityRenderer.h>

#include "Game/Scene/Object/Duck.h"

namespace Sandbox
{
    /// Duck manager class for managing all ducks in the scene
    class DuckManager
    {
    public:
        DuckManager(const std::shared_ptr<Graphics::Model>& duckModel);

        void Update(float delta);
        void RenderWith(const std::shared_ptr<Graphics::EntityRenderer>& renderer);
        void Manage(const std::shared_ptr<Duck>& projectile);

    private:
        std::shared_ptr<Graphics::Model> _duckModel;
        std::list<std::shared_ptr<Duck>> _ducks;
    };
}

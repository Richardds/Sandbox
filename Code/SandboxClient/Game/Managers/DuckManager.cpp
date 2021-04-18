// ----------------------------------------------------------------------------------------
//  \file       DuckManager.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "DuckManager.h"
#include "IO/Console.h"

void Sandbox::DuckManager::Update(const float delta)
{
    auto it = this->_ducks.begin();

    while (it != this->_ducks.end())
    {
        const auto& duck = (*it);

        duck->IncreaseRotationY(15.0f * delta);
        duck->GoForward(delta);

        ++it;
    }
}

void Sandbox::DuckManager::Manage(const std::shared_ptr<Duck>& duck)
{
    this->_ducks.emplace_back(duck);
}

void Sandbox::DuckManager::RenderWith(const std::shared_ptr<Graphics::EntityRenderer>& renderer)
{
    for (const auto& duck : this->_ducks)
    {
        renderer->Render(duck);
    }
}

// ----------------------------------------------------------------------------------------
//  \file       DuckManager.cpp
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "DuckManager.h"
#include "Util/Random.h"

Sandbox::DuckManager::DuckManager(const std::shared_ptr<Graphics::Model>& duckModel) :
    _duckModel(duckModel)
{
}

void Sandbox::DuckManager::Update(const float delta)
{
    auto it = this->_ducks.begin();

    while (it != this->_ducks.end())
    {
        const auto& duck = (*it);

        if (duck->OutOfRange())
        {
            duck->IncreaseRotationY(Util::Random::Instance().GetReal(120.0f, 240.0f));
        }

        duck->GoForward(delta);

        ++it;
    }
}

void Sandbox::DuckManager::RenderWith(const std::shared_ptr<Graphics::EntityRenderer>& renderer)
{
    for (std::shared_ptr<Duck>& projectile : this->_ducks)
    {
        renderer->Render(projectile);
    }
}

void Sandbox::DuckManager::Manage(const std::shared_ptr<Duck>& projectile)
{
    projectile->SetModel(this->_duckModel);
    this->_ducks.emplace_back(projectile);
}

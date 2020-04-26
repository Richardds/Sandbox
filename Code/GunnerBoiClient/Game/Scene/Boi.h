#pragma once

#include <Graphics/Scene/Player.h>
#include <Graphics/Model.h>

namespace GunnerBoi
{

    class Boi : public Graphics::Player
    {
    public:
        Boi();
        Boi(Math::Vector3f position);
        virtual ~Boi();
    };

}
 
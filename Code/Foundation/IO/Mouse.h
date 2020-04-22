#pragma once

#include <functional>

#include "../Core/Singleton.h"
#include "../Math/Vector.h"

namespace IO
{

    class Mouse
    {
        _Singleton(Mouse)

    public:
        enum Key {
            LEFT = GLFW_MOUSE_BUTTON_1,
            RIGHT = GLFW_MOUSE_BUTTON_2,
            MIDDLE = GLFW_MOUSE_BUTTON_3
        };

        Mouse();
        virtual ~Mouse();
        bool IsKeyPressed(Key key) const;
        Math::Vector2ui GetCoords() const;
        Math::Vector2i GetRelativeMotion();
        Math::Vector2f GetGlCoords() const;
        Math::Vector2f GetRelativeGlMotion();
        void FlushMotion();
        void RegisterScrolling(const std::function<void (float, float)>& callback);
        void DoScroll(float x, float y);

    private:
        std::function<void(float, float)> _scrollCallback;
        Math::Vector2ui _lastMotion;
        Math::Vector2f _lastGlMotion;
    };

}

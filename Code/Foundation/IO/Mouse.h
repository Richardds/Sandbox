// ----------------------------------------------------------------------------------------
//  \file       Mouse.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Singleton.h"
#include "Math/Vector.h"

namespace IO
{
    /// Helper class for reading input from a mouse
    class Mouse
    {
    _Singleton(Mouse)

    public:
        enum class Key
        {
            Left = GLFW_MOUSE_BUTTON_1,
            Right = GLFW_MOUSE_BUTTON_2,
            Middle = GLFW_MOUSE_BUTTON_3
        };

        Mouse();
        bool IsKeyPressed(Key key) const;
        Math::Vector2ui GetCoords() const;
        Math::Vector2i GetRelativeMotion();
        Math::Vector2f GetGlCoords() const;
        Math::Vector2f GetRelativeGlMotion();
        void FlushMotion();
        void RegisterScrolling(const std::function<void (float, float)>& callback);
        void DoScroll(float x, float y) const;

    private:
        std::function<void(float, float)> _scrollCallback;
        Math::Vector2ui _lastMotion;
        Math::Vector2f _lastGlMotion;
    };
}

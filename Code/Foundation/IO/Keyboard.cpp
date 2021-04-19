// ----------------------------------------------------------------------------------------
//  \file       Keyboard.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "IO/Keyboard.h"
#include "Core/Debug.h"
#include "Graphics/Core.h"

bool IO::Keyboard::IsKeyPressed(const Key key) const
{
    return this->GetKeyState(key) == GLFW_PRESS;
}

bool IO::Keyboard::IsControlPressed() const
{
    return this->IsKeyPressed(Key::LeftControl);
}

bool IO::Keyboard::IsAltPressed() const
{
    return this->IsKeyPressed(Key::LeftAlt);
}

bool IO::Keyboard::IsShiftPressed() const
{
    return this->IsKeyPressed(Key::LeftShift);
}

int IO::Keyboard::GetKeyState(Key key) const
{
    _Assert(Graphics::Core::Instance().IsCreated())

    const std::shared_ptr<Graphics::Window> context = Graphics::Core::Instance().GetRenderingContext();

    _Assert(context)
    _Assert(context->IsCreated())

    return glfwGetKey(
        context->GetGlfwWindow(),
        static_cast<std::underlying_type<Key>::type>(key)
    );
}

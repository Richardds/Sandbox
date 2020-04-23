#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Keyboard.h"
#include "../Core/Debug.h"
#include "../Graphics/Core.h"

IO::Keyboard::Keyboard()
{
}

IO::Keyboard::~Keyboard()
{
}

bool IO::Keyboard::IsKeyPressed(Key key) const
{
    _assert(Graphics::Core::Instance().IsCreated());

    return glfwGetKey(
        Graphics::Core::Instance().GetRenderingContext()->GetGlfwWindow(),
        static_cast<std::underlying_type<Key>::type>(key)
    );
}

bool IO::Keyboard::IsAltPressed() const
{
    return this->IsKeyPressed(Key::LEFT_ALT);
}

bool IO::Keyboard::IsControlPressed() const
{
    return this->IsKeyPressed(Key::LEFT_CONTROL);
}

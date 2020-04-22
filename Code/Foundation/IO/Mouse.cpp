#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Mouse.h"
#include "../Core/Debug.h"
#include "../Graphics/Core.h"
#include "../Math/Utils.h"

IO::Mouse::Mouse() :
    _lastMotion(0, 0),
    _lastGlMotion(-1.0f, 1.0f)
{
    glfwSetScrollCallback(Graphics::Core::Instance().GetRenderingContext()->GetGlfwWindow(), [](GLFWwindow* window, double x, double y) {
        Mouse::Instance().DoScroll(static_cast<float>(x), static_cast<float>(-y));
    });

    this->FlushMotion();
}

IO::Mouse::~Mouse()
{
}

bool IO::Mouse::IsKeyPressed(Key key) const
{
    _assert(Graphics::Core::Instance().IsCreated());

    return glfwGetMouseButton(Graphics::Core::Instance().GetRenderingContext()->GetGlfwWindow(), key);
}

Math::Vector2ui IO::Mouse::GetCoords() const
{
    std::shared_ptr<Graphics::Window> context = Graphics::Core::Instance().GetRenderingContext();
    double x, y;
    glfwGetCursorPos(context->GetGlfwWindow(), &x, &y);

    return Math::Vector2ui(
        Math::Restrict(static_cast<unsigned int>(x), 0u, context->GetWidth()),
        Math::Restrict(static_cast<unsigned int>(y), 0u, context->GetHeight())
    );
}

Math::Vector2i IO::Mouse::GetRelativeMotion()
{
    Math::Vector2ui currentCoords = this->GetCoords();
    Math::Vector2ui relativeCoords = currentCoords - this->_lastMotion;
    this->_lastMotion = currentCoords;
    return relativeCoords;
}

Math::Vector2f IO::Mouse::GetGlCoords() const
{
    std::shared_ptr<Graphics::Window> context = Graphics::Core::Instance().GetRenderingContext();
    Math::Vector2ui coords = this->GetCoords();
    
    return Math::Vector2f(
        2 * (static_cast<float>(coords.x) / static_cast<float>(context->GetWidth()) - 0.5f),
        -2 * (static_cast<float>(coords.y) / static_cast<float>(context->GetHeight()) - 0.5f)
    );
}

Math::Vector2f IO::Mouse::GetRelativeGlMotion()
{
    Math::Vector2f currentGlCoords = this->GetGlCoords();
    Math::Vector2f relativeGlCoords = currentGlCoords - this->_lastGlMotion;
    this->_lastGlMotion = currentGlCoords;
    return relativeGlCoords;
}

void IO::Mouse::FlushMotion()
{
    this->_lastMotion = this->GetCoords();
    this->_lastGlMotion = this->GetGlCoords();
}

void IO::Mouse::RegisterScrolling(const std::function<void(float, float)>& callback)
{
    this->_scrollCallback = callback;
}

void IO::Mouse::DoScroll(float x, float y)
{
    _assert(this->_scrollCallback);

    this->_scrollCallback(x, y);
}

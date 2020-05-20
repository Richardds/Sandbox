#include "Keyboard.h"
#include "../Core/Debug.h"
#include "../Core/Types.h"
#include "../Graphics/Core.h"

bool IO::Keyboard::IsKeyPressed(Key key) const
{
	_Assert(Graphics::Core::Instance().IsCreated());

	return glfwGetKey(
		Graphics::Core::Instance().GetRenderingContext()->GetGlfwWindow(),
		static_cast<std::underlying_type<Key>::type>(key)
	);
}

bool IO::Keyboard::IsAltPressed() const
{
	return this->IsKeyPressed(Key::LeftAlt);
}

bool IO::Keyboard::IsControlPressed() const
{
	return this->IsKeyPressed(Key::LeftControl);
}

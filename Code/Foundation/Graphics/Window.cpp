#include "Window.h"

#include <utility>
#include "Core.h"

Graphics::Window::Window() :
	_isCreated(false),
	_width(1280),
	_height(720),
	_glfwWindow(nullptr)
{
}

Graphics::Window::Window(const unsigned int width, const unsigned int height, std::string title) :
	_isCreated(false),
	_width(width),
	_height(height),
	_title(std::move(title)),
	_glfwWindow(nullptr)
{
}

Graphics::Window::~Window()
{
	_Assert(!this->IsCreated());
}

bool Graphics::Window::Create()
{
	_Assert(!this->IsCreated());
	_Assert(Core::Instance().IsCreated());

	this->_glfwWindow = glfwCreateWindow(
		static_cast<int>(this->_width),
		static_cast<int>(this->_height),
		this->_title.c_str(),
		nullptr,
		NULL
	);

	_Assert(nullptr != this->_glfwWindow);

	this->_isCreated = true;

	return true;
}

void Graphics::Window::Open() const
{
	glfwShowWindow(this->_glfwWindow);
}

void Graphics::Window::Close() const
{
	glfwHideWindow(this->_glfwWindow);
}

void Graphics::Window::Destroy()
{
	_Assert(this->IsCreated());

	glfwDestroyWindow(this->_glfwWindow);

	this->_isCreated = false;
}

void Graphics::Window::SwapBuffers() const
{
	_Assert(this->IsCreated());
	glfwSwapBuffers(this->_glfwWindow);
}

bool Graphics::Window::IsCloseRequested() const
{
	_Assert(this->IsCreated());
	return glfwWindowShouldClose(this->_glfwWindow);
}

float Graphics::Window::GetAspectRatio() const
{
	return static_cast<float>(this->_width) / static_cast<float>(this->_height);
}

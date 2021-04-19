// ----------------------------------------------------------------------------------------
//  \file       Core.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include "Libraries.h"
#include "Graphics/Core.h"
#include "Core/Debug.h"
#include "Graphics/Buffer.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/Texture.h"
#include "Graphics/VertexArray.h"
#include "IO/Console.h"

Graphics::Core::Core() :
    _isCreated(false)
{
}

Graphics::Core::~Core()
{
    if (this->_isCreated)
    {
        this->Destroy();
    }
}

bool Graphics::Core::Setup()
{
    _Assert(!this->IsCreated())

    glfwSetErrorCallback(GlfwErrorCallback);

    if (glfwInit() != GLFW_TRUE)
    {
        IO::Console::Instance().Error("Failed to initialize GLFW\n");
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#else
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_FALSE);
#endif

    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->_isCreated = true;

    return true;
}

void Graphics::Core::Destroy()
{
    _Assert(this->IsCreated())

    glfwTerminate();

    this->_isCreated = false;
}

bool Graphics::Core::SetRenderingContext(const std::shared_ptr<Window>& window)
{
    _Assert(this->IsCreated())
    _Assert(window->IsCreated())

    this->_context = window;

    glfwMakeContextCurrent(window->GetGlfwWindow());

    const GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK)
    {
        IO::Console::Instance().Error("Failed to initialize GLEW: %s\n", glewGetErrorString(glewStatus));
        return false;
    }

#ifdef _DEBUG
    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(GlDebugCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
#endif

    return true;
}

void Graphics::Core::Debug(const std::string& message)
{
    glDebugMessageInsert(
        GL_DEBUG_SOURCE_APPLICATION,
        GL_DEBUG_TYPE_OTHER,
        0,
        GL_DEBUG_SEVERITY_NOTIFICATION,
        static_cast<GLsizei>(message.length()),
        message.c_str()
    );
}

std::string Graphics::Core::GetGlString(const GLenum name) const
{
    const GLubyte* string_ptr = glGetString(name);

    _Assert(nullptr != string_ptr)

    return std::string(reinterpret_cast<const char*>(string_ptr));
}

Math::Vector4ui Graphics::Core::GetViewport() const
{
    Math::Vector4f viewport;
    glGetFloatv(GL_VIEWPORT, value_ptr(viewport));

    return Math::Vector4ui(
        static_cast<unsigned int>(viewport.x),
        static_cast<unsigned int>(viewport.y),
        static_cast<unsigned int>(viewport.z),
        static_cast<unsigned int>(viewport.w)
    );
}

Math::Vector2f Graphics::Core::GetResolution() const
{
    const Math::Vector4f viewport = this->GetViewport();

    return Math::Vector2f(viewport.z, viewport.w);
}

std::shared_ptr<Graphics::Projection> Graphics::Core::CreateProjection(float fieldOfView) const
{
    return std::make_shared<Projection>(this->_context->GetAspectRatio(), fieldOfView, 0.1f, 1000.0f);
}

std::string Graphics::Core::GetDeviceVendor() const
{
    return this->GetGlString(GL_VENDOR);
}

std::string Graphics::Core::GetDeviceName() const
{
    return this->GetGlString(GL_RENDERER);
}

std::string Graphics::Core::GetDriverVersion() const
{
    return this->GetGlString(GL_VERSION);
}

std::string Graphics::Core::GetGlDump() const
{
    char stateBuffer[2048];

    snprintf(stateBuffer, 2048,
              "- Shader program:                 %u\n"
              "- VertexArray:                    %u\n"
              "- Buffers:\n"
              "  - GL_ARRAY_BUFFER:              %u\n"
              "  - GL_ELEMENT_ARRAY_BUFFER:      %u\n"
              "  - GL_TEXTURE_BUFFER:            %u\n"
              "  - GL_ATOMIC_COUNTER_BUFFER:     %u\n"
              "  - GL_COPY_READ_BUFFER:          %u\n"
              "  - GL_COPY_WRITE_BUFFER:         %u\n"
              "  - GL_DISPATCH_INDIRECT_BUFFER:  %u\n"
              "  - GL_DRAW_INDIRECT_BUFFER:      %u\n"
              "  - GL_PIXEL_PACK_BUFFER:         %u\n"
              "  - GL_PIXEL_UNPACK_BUFFER:       %u\n"
              "  - GL_QUERY_BUFFER:              %u\n"
              "  - GL_SHADER_STORAGE_BUFFER:     %u\n"
              "  - GL_TRANSFORM_FEEDBACK_BUFFER: %u\n"
              "  - GL_UNIFORM_BUFFER:            %u\n"
              "- Textures:\n"
              "  - GL_TEXTURE_1D:                %u\n"
              "  - GL_TEXTURE_2D:                %u\n"
              "  - GL_TEXTURE_3D:                %u\n"
              "- Texture banks:\n"
              "  - GL_TEXTURE0:                  ?\n"
              "    ...\n"
              "  - GL_TEXTURE15:                 ?\n",
              ShaderProgram::GetInUse(),
              VertexArray::GetBound(),
              Buffer::GetBound(GL_ARRAY_BUFFER),
              Buffer::GetBound(GL_ELEMENT_ARRAY_BUFFER),
              Buffer::GetBound(GL_TEXTURE_BUFFER),
              Buffer::GetBound(GL_ATOMIC_COUNTER_BUFFER),
              Buffer::GetBound(GL_COPY_READ_BUFFER),
              Buffer::GetBound(GL_COPY_WRITE_BUFFER),
              Buffer::GetBound(GL_DISPATCH_INDIRECT_BUFFER),
              Buffer::GetBound(GL_DRAW_INDIRECT_BUFFER),
              Buffer::GetBound(GL_PIXEL_PACK_BUFFER),
              Buffer::GetBound(GL_PIXEL_UNPACK_BUFFER),
              Buffer::GetBound(GL_QUERY_BUFFER),
              Buffer::GetBound(GL_SHADER_STORAGE_BUFFER),
              Buffer::GetBound(GL_TRANSFORM_FEEDBACK_BUFFER),
              Buffer::GetBound(GL_UNIFORM_BUFFER),
              Texture::GetBound(GL_TEXTURE_1D),
              Texture::GetBound(GL_TEXTURE_2D),
              Texture::GetBound(GL_TEXTURE_3D)
    );

    return std::string(stateBuffer);
}

float Graphics::Core::GetMaxAnisotropicFiltering() const
{
    float maxAnisotropicFiltering;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropicFiltering);

    return maxAnisotropicFiltering;
}

void Graphics::Core::GlfwErrorCallback(const int errorCode, const char* description)
{
    IO::Console::Instance().Error("GLFW error (%d): %s\n", errorCode, description);
}

void Graphics::Core::GlDebugCallback(
    const GLenum source,
    const GLenum type,
    const GLuint id,
    const GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam
)
{
    const char* sourceStr;
    const char* typeStr;
    const char* severityStr;

    switch (id)
    {
    case 131169:
    case 131185:
    case 131204:
    case 131218:
        return;
    default: ;
    }

    switch (source)
    {
    case GL_DEBUG_SOURCE_API: sourceStr = "API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM: sourceStr = "Window System";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceStr = "Shader Compiler";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY: sourceStr = "Third Party";
        break;
    case GL_DEBUG_SOURCE_APPLICATION: sourceStr = "Application";
        break;
    case GL_DEBUG_SOURCE_OTHER: sourceStr = "Other";
        break;
    default: sourceStr = "Unknown";
    }

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR: typeStr = "Error";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeStr = "Deprecated";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: typeStr = "Undefined";
        break;
    case GL_DEBUG_TYPE_PORTABILITY: typeStr = "Portability";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE: typeStr = "Performance";
        break;
    case GL_DEBUG_TYPE_MARKER: typeStr = "Marker";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP: typeStr = "Push Group";
        break;
    case GL_DEBUG_TYPE_POP_GROUP: typeStr = "Pop Group";
        break;
    case GL_DEBUG_TYPE_OTHER: typeStr = "Other";
        break;
    default: typeStr = "Unknown";
    }

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH: severityStr = "High";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM: severityStr = "Medium";
        break;
    case GL_DEBUG_SEVERITY_LOW: severityStr = "Low";
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: severityStr = "Notification";
        break;
    default: severityStr = "Unknown";
    }

    const std::string glDump = Instance().GetGlDump();

    IO::Console::Instance().Error(
        "\n"
        "OpenGL Debug call (%u) received from '%s':\n"
        "Message: %s\n"
        "Severity: %s\n"
        "Type: %s\n"
        "OpenGL State:\n"
        "%s",
        id, sourceStr, message, severityStr, typeStr, glDump.c_str()
    );

    _AssertMessage(false, "OpenGL debug message")
}

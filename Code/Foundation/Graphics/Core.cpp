#include "Core.h"
#include "../Core/Debug.h"
#include "../IO/Console.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "../Math/Utils.h"

Graphics::Core::Core() :
    _isCreated(false)
{
}

Graphics::Core::~Core()
{
    _assert(!this->IsCreated());
}

bool Graphics::Core::Setup()
{
    _assert(!this->IsCreated());

    if (glfwInit() != GLFW_TRUE) {
        IO::Console::Instance().Error("Failed to initialize GLFW\n");
        return false;
    }

    glfwSetErrorCallback(Core::glfwErrorCallback);

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Core::OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Core::OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
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
    _assert(this->IsCreated());

    glfwTerminate();

    this->_isCreated = false;
}

bool Graphics::Core::SetRenderingContext(std::shared_ptr<Window> window)
{
    _assert(this->IsCreated());
    _assert(window->IsCreated());

    this->_context = window;

    glfwMakeContextCurrent(window->GetGlfwWindow());

    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK) {
        IO::Console::Instance().Error("Failed to initialize GLEW: %s\n", glewGetErrorString(glewStatus));
        return false;
    }

#ifdef _DEBUG
    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(Core::glDebugCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
#endif

    return true;
}

std::string Graphics::Core::GetGlString(GLenum name) const
{
    const GLubyte* string_ptr = glGetString(name);

    _assert(nullptr != string_ptr);

    return std::string(reinterpret_cast<const char*>(string_ptr));;
}

Math::Vector4ui Graphics::Core::GetViewport() const
{
    Math::Vector4f viewport;
    glGetFloatv(GL_VIEWPORT, glm::value_ptr(viewport));

    return Math::Vector4ui(
        static_cast<unsigned int>(viewport.x),
        static_cast<unsigned int>(viewport.y),
        static_cast<unsigned int>(viewport.z),
        static_cast<unsigned int>(viewport.w)
    );
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

    sprintf_s(stateBuffer, 2048,
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

void Graphics::Core::glfwErrorCallback(int errorCode, const char* description)
{
    IO::Console::Instance().Error("GLFW error (%d): %s\n", errorCode, description);
}

void Graphics::Core::glDebugCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam
)
{
    const char* unknown = "Unknown";
    const char* source_str = unknown;
    const char* type_str = unknown;
    const char* severity_str = unknown;

    switch (id)
    {
    case 131169:
    case 131185:
    case 131204:
    case 131218:
        return;
    }

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:               source_str = "API";             break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:     source_str = "Window System";   break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:   source_str = "Shader Compiler"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:       source_str = "Third Party";     break;
    case GL_DEBUG_SOURCE_APPLICATION:       source_str = "Application";     break;
    case GL_DEBUG_SOURCE_OTHER:             source_str = "Other";           break;
    }

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:               type_str = "Error";             break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: type_str = "Deprecated";        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  type_str = "Undefined";         break;
    case GL_DEBUG_TYPE_PORTABILITY:         type_str = "Portability";       break;
    case GL_DEBUG_TYPE_PERFORMANCE:         type_str = "Performance";       break;
    case GL_DEBUG_TYPE_MARKER:              type_str = "Marker";            break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          type_str = "Push Group";        break;
    case GL_DEBUG_TYPE_POP_GROUP:           type_str = "Pop Group";         break;
    case GL_DEBUG_TYPE_OTHER:               type_str = "Other";             break;
    } 

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:            severity_str = "High";          break;
    case GL_DEBUG_SEVERITY_MEDIUM:          severity_str = "Medium";        break;
    case GL_DEBUG_SEVERITY_LOW:             severity_str = "Low";           break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:    severity_str = "Notification";  break;
    }

    std::string glDump = Core::Instance().GetGlDump();

    IO::Console::Instance().Error(
        "\n"
        "OpenGL Debug call (%u) received from '%s':\n"
        "Message: %s\n"
        "Severity: %s\n"
        "Type: %s\n"
        "OpenGL State:\n"
        "%s",
        id, source_str, message, severity_str, type_str, glDump.c_str()
    );

    _assert_msg(false, "OpenGL debug message");
}

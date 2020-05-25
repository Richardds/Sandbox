#version 430 core

layout (location = 0) in vec3 a_Position;

out vec3 position;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    // Pass interpolated position coordinates as texture coordinates
    position = a_Position;

    gl_Position = projection * view * vec4(a_Position, 1.0f);
}

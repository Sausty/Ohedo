#version 450

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoords;

uniform mat4 u_Transform;

out vec2 f_TexCoords;

void main()
{
    f_TexCoords = a_TexCoords;
    gl_Position = u_Transform * vec4(a_Position, 1.0);
}
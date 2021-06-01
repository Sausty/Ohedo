#version 450

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_Texcoords;

uniform mat4 u_Camera;
uniform mat4 u_Transform;

out vec2 f_Texcoords;
out vec3 f_Normal;

void main()
{
    f_Texcoords = a_Texcoords;
    f_Normal = a_Normal;
    gl_Position = u_Transform * u_Camera * vec4(a_Position, 1.0);
}
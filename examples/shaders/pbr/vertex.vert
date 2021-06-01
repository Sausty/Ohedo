#version 450

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_Texcoords;

uniform mat4 u_Camera;
uniform mat4 u_Transform;

out vec2 f_Texcoords;
out vec3 f_WorldPos;
out vec3 f_Normal;

void main()
{
    vec2 flipped = vec2(a_Texcoords.x, 1.0 - a_Texcoords.y);

    f_Texcoords = flipped;
    f_Normal = mat3(u_Transform) * a_Normal;
    f_WorldPos = vec3(u_Transform * vec4(a_Position, 1.0));

    gl_Position = vec4(a_Position, 1.0) * u_Transform * u_Camera;
}
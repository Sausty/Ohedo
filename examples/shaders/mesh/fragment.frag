#version 450

out vec4 FragColor;

uniform sampler2D u_AlbedoTexture;

in vec2 f_Texcoords;
in vec3 f_Normal;

void main()
{
    FragColor = texture(u_AlbedoTexture, f_Texcoords);
}
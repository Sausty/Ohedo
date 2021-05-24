#version 450

layout (location = 0) out vec4 FragColor;

in vec2 f_TexCoords;

uniform sampler2D u_Texture;

void main()
{
    vec4 color = texture(u_Texture, f_TexCoords);

    if (color.a < 0.2)
        discard;

    FragColor = color;
}
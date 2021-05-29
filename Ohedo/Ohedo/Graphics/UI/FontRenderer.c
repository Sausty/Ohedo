#include "TextRenderer.h"

#include <Ohedo/Graphics/Shader.h>
#include <glad/glad.h>
#include <stdio.h>

Ohedo_Define_Struct(Ohedo_TextRendererData)
struct Ohedo_TextRendererData
{
    u32 VAO;
    u32 VBO;
    Ohedo_Shader shader;
    Ohedo_Mat4 projection;
};

static Ohedo_TextRendererData s_Data;

void Ohedo_InitTextRenderer(Ohedo_Vec2 viewportSize)
{
    // Shader
    char* vertexShader = "#version 330 core\nlayout(location = 0) in vec4 vertex;\nout vec2 TexCoords;\n\nuniform mat4 projection;\n\nvoid main()\n{\n\tvec4 pos = projection * vec4(vertex.xy, 0.0, 1.0);\n\tgl_Position = vec4(pos.xy, 0.0, 1.0);\n\tTexCoords = vertex.zw;\n}";
    char* fragmentShader = "#version 330 core\nin vec2 TexCoords;\nout vec4 color;\n\nuniform sampler2D text;\nuniform vec3 textColor;\n\nvoid main()\n{\n\tvec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n\tcolor = vec4(textColor, 1.0) * sampled;\n}";

    s_Data.shader = Ohedo_CreateShaderFromSource(vertexShader, fragmentShader);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenVertexArrays(1, &s_Data.VAO);
    glGenBuffers(1, &s_Data.VBO);
    glBindVertexArray(s_Data.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, s_Data.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    s_Data.projection = Ohedo_Mat4_Orthographic(0.0f, viewportSize.x, 0.0f, viewportSize.y, 0.01f, 100.0f);
    
    Ohedo_BindShader(s_Data.shader);
    Ohedo_ShaderUniformMat4(s_Data.shader, "projection", s_Data.projection);
    Ohedo_UnbindShader();
}

void Ohedo_ShutdownTextRenderer()
{
    Ohedo_DeleteShader(s_Data.shader);
    glDeleteBuffers(1, &s_Data.VBO);
    glDeleteVertexArrays(1, &s_Data.VAO);
}

void Ohedo_ResizeFontRenderer(Ohedo_Vec2 viewportSize)
{
    s_Data.projection = Ohedo_Mat4_Orthographic(0.0f, viewportSize.x, 0.0f, viewportSize.y, 0.1f, 100.0f);
}

void Ohedo_DrawText(Ohedo_Font font, char* text, float x, float y, f32 scale, Ohedo_Vec3 color)
{
    Ohedo_BindShader(s_Data.shader);
    Ohedo_ShaderUniformMat4(s_Data.shader, "projection", s_Data.projection);
    Ohedo_ShaderUniformFloat3(s_Data.shader, "textColor", color);
    Ohedo_ShaderUniformInt(s_Data.shader, "text", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(s_Data.VAO);

    for (int i = 0; i < strlen(text); i++)
    {
        char character = text[i];

        Ohedo_FontCharacter ch;
        for (i32 i = 0; i < 128; i++)
        {
            if (font.characters[i].ascii_code == character)
                ch = font.characters[i];
        }

        float xpos = x + ch.bearing.x * scale;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };

        glBindTexture(GL_TEXTURE_2D, ch.texture);
        glBindBuffer(GL_ARRAY_BUFFER, s_Data.VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (ch.advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    Ohedo_UnbindShader();
}
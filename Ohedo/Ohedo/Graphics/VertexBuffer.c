#include "VertexBuffer.h"

#include <glad/glad.h>

Ohedo_VertexBuffer Ohedo_CreateVertexBuffer(void* vertices, u32 size)
{
    Ohedo_VertexBuffer vbo;

    glGenBuffers(1, &vbo.id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo.id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo;
}

Ohedo_VertexBuffer Ohedo_CreateVertexBufferEmpty(u32 size)
{
    Ohedo_VertexBuffer vbo;
    
    glGenBuffers(1, &vbo.id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo.id);
    glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo;
}

void Ohedo_DeleteVertexBuffer(Ohedo_VertexBuffer buffer)
{
    glDeleteBuffers(1, &buffer.id);
}

void Ohedo_BindVertexBuffer(Ohedo_VertexBuffer buffer)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer.id);
}

void Ohedo_UnbindVertexBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Ohedo_SetVertexBufferData(Ohedo_VertexBuffer buffer, void* data, u32 size)
{
    Ohedo_BindVertexBuffer(buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    Ohedo_UnbindVertexBuffer();
}
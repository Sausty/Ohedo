#include "IndexBuffer.h"

#include <glad/glad.h>

Ohedo_IndexBuffer Ohedo_CreateIndexBuffer(u32* indices, u32 size)
{
    Ohedo_IndexBuffer vbo;

    glGenBuffers(1, &vbo.id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return vbo;
}

void Ohedo_SetIndexBufferType(Ohedo_IndexBuffer buffer, Ohedo_IndexType type)
{
    buffer.type = type;
}

void Ohedo_DeleteIndexBuffer(Ohedo_IndexBuffer buffer)
{
    glDeleteBuffers(1, &buffer.id);
}

void Ohedo_BindIndexBuffer(Ohedo_IndexBuffer buffer)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.id);
}

void Ohedo_UnbindIndexBuffer()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
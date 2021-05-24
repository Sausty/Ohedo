#include "VertexArray.h"

#include <glad/glad.h>

i32 AttributeTypeGL(Ohedo_VertexAttributeType type)
{
    switch (type)
    {
    case Ohedo_VertexAttributeType_Float:
        return GL_FLOAT;
    case Ohedo_VertexAttributeType_Int:
        return GL_INT;
    default:
        return 0;
    }
}

Ohedo_VertexArray Ohedo_CreateVertexArray()
{
    Ohedo_VertexArray arr;
    glGenVertexArrays(1, &arr.id);
    return arr;
}

void Ohedo_BindVertexArray(Ohedo_VertexArray vao)
{
    glBindVertexArray(vao.id);
}

void Ohedo_UnbindVertexArray()
{
    glBindVertexArray(0);
}

void Ohedo_DeleteVertexArray(Ohedo_VertexArray vao)
{
    glDeleteVertexArrays(1, &vao.id);
}

void Ohedo_AddVertexAttribute(i32 index, i32 attributeSize, i32 stride, i32 offset, Ohedo_VertexAttributeType type)
{
    glVertexAttribPointer(index, attributeSize, AttributeTypeGL(type), GL_FALSE, stride, (void*)offset);
    glEnableVertexAttribArray(index);
}
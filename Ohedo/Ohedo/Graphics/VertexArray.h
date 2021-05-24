#ifndef OHEDO_VERTEX_ARRAY_H
#define OHEDO_VERTEX_ARRAY_H

#include <Ohedo/Utils/Types.h>

typedef enum Ohedo_VertexAttributeType Ohedo_VertexAttributeType;
enum Ohedo_VertexAttributeType
{
    Ohedo_VertexAttributeType_Float,
    Ohedo_VertexAttributeType_Int
};

typedef struct Ohedo_VertexArray Ohedo_VertexArray;
struct Ohedo_VertexArray
{
    RenderID id;
};

Ohedo_VertexArray Ohedo_CreateVertexArray();
void Ohedo_BindVertexArray(Ohedo_VertexArray vao);
void Ohedo_UnbindVertexArray();
void Ohedo_DeleteVertexArray(Ohedo_VertexArray vao);

void Ohedo_AddVertexAttribute(i32 index, i32 attributeSize, i32 stride, i32 offset, Ohedo_VertexAttributeType type);

#endif
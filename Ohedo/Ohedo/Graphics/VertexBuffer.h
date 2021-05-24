#ifndef OHEDO_VERTEXBUFFER_H
#define OHEDO_VERTEXBUFFER_H

#include <Ohedo/Utils/Types.h>

Ohedo_Define_Struct(Ohedo_VertexBuffer)
struct Ohedo_VertexBuffer
{
    RenderID id;
};

Ohedo_VertexBuffer Ohedo_CreateVertexBuffer(void* vertices, u32 size);
Ohedo_VertexBuffer Ohedo_CreateVertexBufferEmpty(u32 size);
void Ohedo_DeleteVertexBuffer(Ohedo_VertexBuffer buffer);
void Ohedo_BindVertexBuffer(Ohedo_VertexBuffer buffer);
void Ohedo_UnbindVertexBuffer();
void Ohedo_SetVertexBufferData(Ohedo_VertexBuffer buffer, void* data, u32 size);

#endif
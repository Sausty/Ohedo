#ifndef OHEDO_INDEXBUFFER_H
#define OHEDO_INDEXBUFFER_H

#include <Ohedo/Utils/Types.h>

typedef struct Ohedo_IndexBuffer Ohedo_IndexBuffer;
struct Ohedo_IndexBuffer
{
    RenderID id;
};

Ohedo_IndexBuffer Ohedo_CreateIndexBuffer(u32* indices, u32 size);
void Ohedo_DeleteIndexBuffer(Ohedo_IndexBuffer buffer);
void Ohedo_BindIndexBuffer(Ohedo_IndexBuffer buffer);
void Ohedo_UnbindIndexBuffer();

#endif
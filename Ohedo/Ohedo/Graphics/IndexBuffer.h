#ifndef OHEDO_INDEXBUFFER_H
#define OHEDO_INDEXBUFFER_H

#include <Ohedo/Utils/Types.h>

Ohedo_Define_Enum(Ohedo_IndexType)
enum Ohedo_IndexType
{
    Ohedo_IndexType_Byte = 1,
    Ohedo_IndexType_Short = 2,
    Ohedo_IndexType_UInt = 3
};

Ohedo_Define_Struct(Ohedo_IndexBuffer)
struct Ohedo_IndexBuffer
{
    RenderID id;
    Ohedo_IndexType type;
};

Ohedo_IndexBuffer Ohedo_CreateIndexBuffer(u32* indices, u32 size);
void Ohedo_SetIndexBufferType(Ohedo_IndexBuffer buffer, Ohedo_IndexType type);
void Ohedo_DeleteIndexBuffer(Ohedo_IndexBuffer buffer);
void Ohedo_BindIndexBuffer(Ohedo_IndexBuffer buffer);
void Ohedo_UnbindIndexBuffer();

#endif
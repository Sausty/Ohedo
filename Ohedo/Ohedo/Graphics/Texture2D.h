#ifndef OHEDO_TEXTURE2D_H
#define OHEDO_TEXTURE2D_H

#include <Ohedo/Utils/Types.h>

Ohedo_Define_Struct(Ohedo_Texture2D)
struct Ohedo_Texture2D
{
    RenderID id;
    i32 width;
    i32 height;
    i32 channels;
};

// Texture creation

Ohedo_Texture2D Ohedo_CreateTextureFromFile(char* path, i32 genMips);
Ohedo_Texture2D Ohedo_CreateFloatTextureFromFile(char* path, i32 genMips);
Ohedo_Texture2D Ohedo_CreateTextureFromMemory(void* data, i32 width, i32 height, i32 genMips);
Ohedo_Texture2D Ohedo_CreateFloatTextureFromMemory(f32* data, i32 width, i32 height, i32 genMips);

void Ohedo_DeleteTexture(Ohedo_Texture2D texture);
void Ohedo_SetActiveTexture(int slot);
void Ohedo_BindTexture2D(Ohedo_Texture2D texture);
void Ohedo_UnbindTexture2D();

#endif
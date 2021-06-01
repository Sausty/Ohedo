#ifndef OHEDO_MATERIAL_H
#define OHEDO_MATERIAL_H

#include <Ohedo/Utils/Types.h>
#include <Ohedo/Graphics/Shader.h>
#include <Ohedo/Graphics/Texture2D.h>

#define OHEDO_MAX_MATERIAL_TEXTURES 32

Ohedo_Define_Struct(Ohedo_Material)
typedef void(*Ohedo_MaterialUpdateCallback)(Ohedo_Material*);

struct Ohedo_Material
{
    Ohedo_Shader shader;
    Ohedo_Texture2D textures[OHEDO_MAX_MATERIAL_TEXTURES];
    i32 textureCount;
    char* textureNames[OHEDO_MAX_MATERIAL_TEXTURES];
    Ohedo_MaterialUpdateCallback updateCallback;
};

Ohedo_Material Ohedo_CreateMaterial(Ohedo_Shader shader);
void Ohedo_FreeMaterial(Ohedo_Material material);
void Ohedo_SetMaterialUpdateCallback(Ohedo_Material* material, Ohedo_MaterialUpdateCallback cb);
void Ohedo_AddMaterialTexture(Ohedo_Material* material, Ohedo_Texture2D texture, char* textureName);
void Ohedo_ModifyTexture(Ohedo_Material* material, Ohedo_Texture2D texture, i32 textureIndex);
void Ohedo_RemoveTexture(Ohedo_Material* material, Ohedo_Texture2D texture);
void Ohedo_BindMaterial(Ohedo_Material* material);
void Ohedo_UnbindMaterial(Ohedo_Material material);

#endif
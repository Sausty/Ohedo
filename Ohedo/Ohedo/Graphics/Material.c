#include "Material.h"

Ohedo_Material Ohedo_CreateMaterial(Ohedo_Shader shader)
{
    Ohedo_Material result;
    memset(&result, 0, sizeof(Ohedo_Material));
    result.shader = shader;
    result.textureCount = 0;
    return result;
}

void Ohedo_FreeMaterial(Ohedo_Material material)
{
    for (i32 i = 0; i < material.textureCount; i++)
        Ohedo_DeleteTexture(material.textures[i]);
    Ohedo_DeleteShader(material.shader);
}

void Ohedo_SetMaterialUpdateCallback(Ohedo_Material* material, Ohedo_MaterialUpdateCallback cb)
{
    material->updateCallback = cb;
}

void Ohedo_AddMaterialTexture(Ohedo_Material* material, Ohedo_Texture2D texture, char* textureName)
{
    material->textures[material->textureCount] = texture;
    material->textureNames[material->textureCount] = textureName;
    material->textureCount++;
}

void Ohedo_ModifyTexture(Ohedo_Material* material, Ohedo_Texture2D texture, i32 textureIndex)
{
    material->textures[textureIndex] = texture;
}

void Ohedo_RemoveTexture(Ohedo_Material* material, Ohedo_Texture2D texture)
{
    for (i32 i = 0; i < material->textureCount; i++)
    {
        if (material->textures[i].id == texture.id)
        {
            material->textures[i].id = -1;
            break;
        }
    }
}

void Ohedo_BindMaterial(Ohedo_Material* material)
{
    Ohedo_BindShader(material->shader);

    for (i32 i = 0; i < material->textureCount; i++)
    {
        Ohedo_ShaderUniformInt(material->shader, material->textureNames[i], i);
        Ohedo_SetActiveTexture(i);
        Ohedo_BindTexture2D(material->textures[i]);
    }
    
    if (material->updateCallback)
    {
        material->updateCallback(material);
    }
}

void Ohedo_UnbindMaterial(Ohedo_Material material)
{
    Ohedo_UnbindShader(material.shader);
    Ohedo_UnbindTexture2D();
}
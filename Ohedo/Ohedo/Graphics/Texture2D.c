#include "Texture2D.h"

#include "stb_image/stb_image.h"
#include <glad/glad.h>
#include <stdio.h>

Ohedo_Texture2D Ohedo_CreateTextureFromFile(char* path, i32 genMips)
{
    Ohedo_Texture2D result;

    stbi_set_flip_vertically_on_load(1);
    u8* data = stbi_load(path, &result.width, &result.height, &result.channels, 0);

    glGenTextures(1, &result.id);
    glBindTexture(GL_TEXTURE_2D, result.id);

    if (data)
    {
        GLenum format;
        if (result.channels == 1)
            format = GL_RED;
        else if (result.channels == 3)
            format = GL_RGB;
        else if (result.channels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, result.width, result.height, 0, format, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (genMips) {
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        }
        else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
    }
    else
    {
        printf("Ohedo Texture 2D : Failed to load image with path (%s)\n", path);
    }
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return result;
}

Ohedo_Texture2D Ohedo_CreateFloatTextureFromFile(char* path, i32 genMips)
{
    Ohedo_Texture2D result;

    stbi_set_flip_vertically_on_load(1);
    f32* data = stbi_loadf(path, &result.width, &result.height, &result.channels, STBI_rgb_alpha);

    glGenTextures(1, &result.id);
    glBindTexture(GL_TEXTURE_2D, result.id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16, result.width, result.height, 0, GL_RGB16, GL_FLOAT, data);
        if (genMips) glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Ohedo Texture 2D : Failed to load image with path (%s)\n", path);
    }
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return result;
}

Ohedo_Texture2D Ohedo_CreateTextureFromMemory(void* data, i32 width, i32 height, i32 genMips)
{
    Ohedo_Texture2D result;

    glGenTextures(1, &result.id);
    glBindTexture(GL_TEXTURE_2D, result.id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    if (genMips) glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return result;
}

Ohedo_Texture2D Ohedo_CreateFloatTextureFromMemory(f32* data, i32 width, i32 height, i32 genMips)
{
    Ohedo_Texture2D result;

    glGenTextures(1, &result.id);
    glBindTexture(GL_TEXTURE_2D, result.id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16, result.width, result.height, 0, GL_RGB16, GL_FLOAT, data);
    if (genMips) glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return result;
}

void Ohedo_DeleteTexture(Ohedo_Texture2D texture)
{
    glDeleteTextures(1, &texture.id);
}

void Ohedo_SetActiveTexture(int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
}

void Ohedo_BindTexture2D(Ohedo_Texture2D texture)
{
    glBindTexture(GL_TEXTURE_2D, texture.id);
}

void Ohedo_UnbindTexture2D()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
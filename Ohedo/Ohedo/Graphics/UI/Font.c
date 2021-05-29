#include "Font.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glad/glad.h>
#include <stdio.h>

Ohedo_Font Ohedo_LoadFont(char* path, u32 size)
{
    Ohedo_Font font;
    font.fontName = path;

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        printf("Ohedo Font Loader: Failed to initialise FreeType\n");
        exit(-1);
    }

    FT_Face face;
    if (FT_New_Face(ft, path, 0, &face)) {
        printf("Ohedo Font Loader: Failed to load font with path %s\n", path);
        exit(-1);
    }

    FT_Set_Pixel_Sizes(face, 0, size);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (u8 c = 0; c < 128; c++) // fuck c++ we do c99 here boys
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            printf("Ohedo FOnt Loader: Failed to load font glyph %c", c);
            continue;
        }

        RenderID texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Ohedo_FontCharacter character;
        character.texture = texture;
        character.size = Ohedo_Vec2_New(face->glyph->bitmap.width, face->glyph->bitmap.rows);
        character.bearing = Ohedo_Vec2_New(face->glyph->bitmap_left, face->glyph->bitmap_top);
        character.advance = face->glyph->advance.x;
        character.ascii_code = c;

        font.characters[c] = character;
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return font;
}

void Ohedo_FreeFont(Ohedo_Font font)
{
    for (i32 c = 0; c < 128; c++)
    {
        glDeleteTextures(1, &font.characters[c].texture);
    }
}
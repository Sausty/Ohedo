#ifndef OHEDO_FONT_H
#define OHEDO_FONT_H

#include <Ohedo/Utils/Types.h>
#include <Ohedo/Maths/Vec2.h>

Ohedo_Define_Struct(Ohedo_FontCharacter)
struct Ohedo_FontCharacter
{
    u32 texture;
    Ohedo_Vec2 size;
    Ohedo_Vec2 bearing;
    u32 advance;
    u8 ascii_code;
};

Ohedo_Define_Struct(Ohedo_Font)
struct Ohedo_Font
{
    Ohedo_FontCharacter characters[128];
    char* fontName;
};

Ohedo_Font Ohedo_LoadFont(char* path, u32 size);
void Ohedo_FreeFont(Ohedo_Font font);

#endif
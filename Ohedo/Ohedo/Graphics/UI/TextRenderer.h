#ifndef OHEDO_TEXTRENDERER_H
#define OHEDO_TEXTRENDERER_H

#include <Ohedo/Graphics/UI/Font.h>
#include <Ohedo/Maths/Vec3.h>

void Ohedo_InitTextRenderer(Ohedo_Vec2 viewportSize);
void Ohedo_ShutdownTextRenderer();
void Ohedo_ResizeFontRenderer(Ohedo_Vec2 viewportSize);
void Ohedo_DrawText(Ohedo_Font font, char* text, float x, float y, f32 scale, Ohedo_Vec3 color);

#endif
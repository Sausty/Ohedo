#ifndef OHEDO_BATCHRENDERER_H
#define OHEDO_BATCHRENDERER_H

#include <Ohedo/Utils/Types.h>
#include <Ohedo/Maths/Vec2.h>
#include <Ohedo/Maths/Vec3.h>
#include <Ohedo/Maths/Vec4.h>
#include <Ohedo/Maths/Mat4.h>
#include <Ohedo/Graphics/Texture2D.h>

void Ohedo_Batch_Init();
void Ohedo_Batch_Shutdown();

void Ohedo_Batch_Begin(Ohedo_Mat4 viewProjection);
void Ohedo_Batch_End();

void Ohedo_Batch_Draw_Quad(Ohedo_Vec3 pos, Ohedo_Vec2 scale, Ohedo_Vec3 rotation, f32 angle, Ohedo_Vec3 color);
void Ohedo_Batch_Draw_Quad_Mat4(Ohedo_Mat4 transform, Ohedo_Vec3 color);
void Ohedo_Batch_Draw_Textured_Quad(Ohedo_Vec3 pos, Ohedo_Vec2 scale, Ohedo_Vec3 rotation, f32 angle, Ohedo_Vec3 color, Ohedo_Texture2D texture);
void Ohedo_Batch_Draw_Textured_Quad_Mat4(Ohedo_Mat4 transform, Ohedo_Vec3 color, Ohedo_Texture2D texture);

#endif
#ifndef OHEDO_H
#define OHEDO_H

// Utils
#include <Ohedo/Utils/Types.h>
#include <Ohedo/Utils/Window.h>

// Maths
#include <Ohedo/Maths/Vec2.h>
#include <Ohedo/Maths/Vec3.h>
#include <Ohedo/Maths/Vec4.h>
#include <Ohedo/Maths/Mat4.h>

// Graphics
#include <Ohedo/Graphics/RenderCommand.h>
#include <Ohedo/Graphics/Shader.h>
#include <Ohedo/Graphics/VertexArray.h>
#include <Ohedo/Graphics/VertexBuffer.h>
#include <Ohedo/Graphics/IndexBuffer.h>
#include <Ohedo/Graphics/Texture2D.h>

// Init
typedef enum Ohedo_InitFlags Ohedo_InitFlags;
enum Ohedo_InitFlags
{
    Ohedo_InitFlags_Video = 1,
    Ohedo_InitFlags_All = 2
};

i32 Ohedo_Init(Ohedo_InitFlags flags);
void Ohedo_Shutdown();

#endif
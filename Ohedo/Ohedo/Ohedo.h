#ifndef OHEDO_H
#define OHEDO_H

// Utils
#include <Ohedo/Utils/Types.h>
#include <Ohedo/Utils/Window.h>
#include <Ohedo/Utils/InputCodes.h>
#include <Ohedo/Utils/Input.h>
#include <Ohedo/Utils/Timer.h>

// Entity
#include <Ohedo/Entity/Components.h>
#include <Ohedo/Entity/Entity.h>
#include <Ohedo/Entity/Scene.h>

// Maths
#include <Ohedo/Maths/Vec2.h>
#include <Ohedo/Maths/Vec3.h>
#include <Ohedo/Maths/Vec4.h>
#include <Ohedo/Maths/Mat4.h>
#include <Ohedo/Maths/Noise.h>

// Graphics
#include <Ohedo/Graphics/RenderCommand.h>
#include <Ohedo/Graphics/Shader.h>
#include <Ohedo/Graphics/VertexArray.h>
#include <Ohedo/Graphics/VertexBuffer.h>
#include <Ohedo/Graphics/IndexBuffer.h>
#include <Ohedo/Graphics/Texture2D.h>
#include <Ohedo/Graphics/BatchRenderer.h>
#include <Ohedo/Graphics/Material.h>
#include <Ohedo/Graphics/Mesh.h>

// UI
#include <Ohedo/Graphics/UI/Font.h>
#include <Ohedo/Graphics/UI/TextRenderer.h>

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
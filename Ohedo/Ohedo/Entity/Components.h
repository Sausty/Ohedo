#ifndef OHEDO_COMPONENTS_H
#define OHEDO_COMPONENTS_H

#include <Ohedo/Utils/Types.h>
#include <Ohedo/Maths/Vec3.h>
#include <Ohedo/Maths/Mat4.h>
#include <Ohedo/Graphics/Texture2D.h>
#include <Ohedo/Graphics/Material.h>
#include <Ohedo/Graphics/Mesh.h>

Ohedo_Define_Struct(Ohedo_TransformComponent)
struct Ohedo_TransformComponent
{
    Ohedo_Vec3 position;
    Ohedo_Vec3 scale;
    Ohedo_Vec3 rotation;
};

Ohedo_Define_Struct(Ohedo_SpriteRendererComponent)
struct Ohedo_SpriteRendererComponent
{
    Ohedo_Texture2D texture;
    Ohedo_Vec3 color;
};

Ohedo_Define_Struct(Ohedo_QuadColliderComponent)
struct Ohedo_QuadColliderComponent
{
    i32 width;
    i32 height;
    i32 x;
    i32 y;
};

Ohedo_Define_Struct(Ohedo_CameraComponent)
struct Ohedo_CameraComponent
{
    Ohedo_Mat4 pv_matrix;
    i32 primary;
};

Ohedo_Define_Struct(Ohedo_MeshRenderer)
struct Ohedo_MeshRenderer
{
    Ohedo_Mesh mesh;
    Ohedo_Material material;
};

#endif
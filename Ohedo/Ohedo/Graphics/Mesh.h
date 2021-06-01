#ifndef OHEDO_MESH_H
#define OHEDO_MESH_H

#include <Ohedo/Utils/Types.h>
#include <Ohedo/Graphics/VertexArray.h>
#include <Ohedo/Graphics/VertexBuffer.h>
#include <Ohedo/Graphics/IndexBuffer.h>
#include <Ohedo/Maths/Vec3.h>
#include <Ohedo/Maths/Vec2.h>

#define OHEDO_MAX_MESH_BUFFERS 132

Ohedo_Define_Struct(Ohedo_MeshVertex)
struct Ohedo_MeshVertex
{
    Ohedo_Vec3 position;
    Ohedo_Vec3 normal;
    Ohedo_Vec2 texcoords;
};

Ohedo_Define_Struct(Ohedo_Mesh)
struct Ohedo_Mesh
{
    Ohedo_VertexArray vao;
    Ohedo_VertexBuffer vbo[OHEDO_MAX_MESH_BUFFERS];
    Ohedo_IndexBuffer ebo[OHEDO_MAX_MESH_BUFFERS];
    i32 drawCounts[OHEDO_MAX_MESH_BUFFERS];
    i32 num_ebos;
    i32 vertexCount;
};

Ohedo_Mesh Ohedo_CreateMeshFromGLTF(char* path);
Ohedo_Mesh Ohedo_CreateMeshFromRawData(Ohedo_MeshVertex* vertices, u32 vertexSize, void* indices, u32 indexSize);
void Ohedo_FreeMesh(Ohedo_Mesh mesh);
void Ohedo_DrawMesh(Ohedo_Mesh mesh);

#endif
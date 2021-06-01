#include "Mesh.h"

#include <glad/glad.h>

#define _CRT_SECURE_NO_WARNINGS
#define CGLTF_IMPLEMENTATION
#include <cgltf.h>
#undef _CRT_SECURE_NO_WARNINGS

#include <assert.h>

#define cgltf_call(call) do { cgltf_result _result = (call); assert(_result == cgltf_result_success); } while(0)

u32 cgltf_component_type_size(cgltf_component_type type)
{
    switch (type)
    {
        case cgltf_component_type_r_8:
        case cgltf_component_type_r_8u:
          return 1;
        case cgltf_component_type_r_16:
        case cgltf_component_type_r_16u:
          return 2;
        case cgltf_component_type_r_32u:
        case cgltf_component_type_r_32f:
          return 4;
    }

    assert(0);
    return 0;
}

u32 cgltf_type_component_count(cgltf_type type) 
{
    switch (type)
    {
        case cgltf_type_scalar:
          return 1;
        case cgltf_type_vec2:
          return 2;
        case cgltf_type_vec3:
          return 3;
        case cgltf_type_vec4:
        case cgltf_type_mat2:
          return 4;
        case cgltf_type_mat3:
          return 9;
        case cgltf_type_mat4:
          return 16;
    }

    assert(0);
    return 0;
}

u32 count_cgltf_node_primitives(cgltf_node* node)
{
    u32 count = 0;

    if(node->mesh)
    {
        count += (u32)node->mesh->primitives_count;
    }

    foreach(childIndex, node->children_count)
    {
        count += count_cgltf_node_primitives(node->children[childIndex]);
    }

    return count;
}

void* query_accessor_data(cgltf_accessor* accessor, u32* componentSize, u32* componentCount)
{
    *componentSize = cgltf_component_type_size(accessor->component_type);
    *componentCount = cgltf_type_component_count(accessor->type);

    cgltf_buffer_view* view = accessor->buffer_view;
    return offset_ptr_bytes(void, view->buffer->data, view->offset);
}

void process_cgltf_primitive(cgltf_primitive* primitive, u32 currentPrimitiveIndex, Ohedo_Mesh* mesh)
{
    cgltf_attribute* positionAttribute = 0;
    cgltf_attribute* texCoordAttribute = 0;
    cgltf_attribute* normalAttribute = 0;

    foreach(attributeIndex, primitive->attributes_count)
    {
        cgltf_attribute* attribute = &primitive->attributes[attributeIndex];

        if(strcmp(attribute->name, "POSITION") == 0) positionAttribute = attribute;
        if(strcmp(attribute->name, "TEXCOORD_0") == 0) texCoordAttribute = attribute;
        if(strcmp(attribute->name, "NORMAL") == 0) normalAttribute = attribute;
    }

    assert(positionAttribute && texCoordAttribute && normalAttribute);

    u32 vertexStrideCount = 8;
    u32 vertexStrideBytes = vertexStrideCount * sizeof(f32);
    u32 vertexCount = (u32)positionAttribute->data->count;
    u32 verticesSize = vertexCount * vertexStrideBytes;
    f32* vertices = (f32*)malloc(verticesSize);

    {
        u32 componentSize, componentCount;
        f32* src = (f32*)query_accessor_data(positionAttribute->data, &componentSize, &componentCount);
        assert(componentSize == 4);

        foreach(vertexIndex, vertexCount)
        {
            u32 internalIndex = vertexIndex * vertexStrideCount;
            vertices[internalIndex + 0] = src[vertexIndex * componentCount + 0];
            vertices[internalIndex + 1] = src[vertexIndex * componentCount + 1];
            vertices[internalIndex + 2] = src[vertexIndex * componentCount + 2];
        }
    }

    {
        u32 componentSize, componentCount;
        f32* src = (f32*)query_accessor_data(normalAttribute->data, &componentSize, &componentCount);
        assert(componentSize == 4);

        foreach(vertexIndex, vertexCount)
        {
            u32 internalIndex = vertexIndex * vertexStrideCount;
            vertices[internalIndex + 3] = src[vertexIndex * componentCount + 0];
            vertices[internalIndex + 4] = src[vertexIndex * componentCount + 1];
            vertices[internalIndex + 5] = src[vertexIndex * componentCount + 2];
        }
    }

    {
        u32 componentSize, componentCount;
        f32* src = (f32*)query_accessor_data(texCoordAttribute->data, &componentSize, &componentCount);
        assert(componentSize == 4);

        foreach(vertexIndex, vertexCount)
        {
            u32 internalIndex = vertexIndex * vertexStrideCount;
            vertices[internalIndex + 6] = src[vertexIndex * componentCount + 0];
            vertices[internalIndex + 7] = src[vertexIndex * componentCount + 1];
        }
    }

    u32 indexCount = (u32)primitive->indices->count;
    u32* indices = (u32*)malloc(indexCount * sizeof(u32));

    {
        u32 componentSize, componentCount;
        void* src = query_accessor_data(primitive->indices, &componentSize, &componentCount);
        assert(componentSize == 4 || componentSize == 2);

        if (componentSize == 2)
        { // u16
            u16* ptr = (u16*)src;
            foreach(indexIndex, indexCount)
            {
                indices[indexIndex] = ptr[indexIndex];
            }
        }
        else
        { // u32
            u32* ptr = (u32*)src;
            foreach(indexIndex, indexCount)
            {
                indices[indexIndex] = ptr[indexIndex];
            }
        }
    }

    mesh->ebo[currentPrimitiveIndex].type = Ohedo_IndexType_UInt;

    mesh->vbo[currentPrimitiveIndex] = Ohedo_CreateVertexBuffer(vertices, verticesSize);
    mesh->ebo[currentPrimitiveIndex] = Ohedo_CreateIndexBuffer(indices, indexCount * sizeof(u32));

    mesh->num_ebos++;

    mesh->drawCounts[currentPrimitiveIndex] = indexCount;

    free(vertices);
    free(indices);

    currentPrimitiveIndex++;
}

void process_cgltf_node(cgltf_node* node, u32 currentPrimitiveIndex, Ohedo_Mesh* mesh)
{
    if(node->mesh)
    {
        foreach(primitiveIndex, node->mesh->primitives_count)
        {
            process_cgltf_primitive(&node->mesh->primitives[primitiveIndex], currentPrimitiveIndex, mesh);
        }
    }

    foreach(childIndex, node->children_count)
    {
        process_cgltf_node(node->children[childIndex], currentPrimitiveIndex, mesh);
    }
}

void allocate_mesh(Ohedo_Mesh* mesh, u32 primitiveCount)
{
    mesh->vertexCount = primitiveCount;
}

Ohedo_Mesh Ohedo_CreateMeshFromGLTF(char* path)
{
    Ohedo_Mesh mesh;
    memset(&mesh, 0, sizeof(Ohedo_Mesh));

    for (i32 i = 0; i < OHEDO_MAX_MESH_BUFFERS; i++)
    {
        memset(&mesh.vbo[i], 0, sizeof(Ohedo_VertexBuffer));
        memset(&mesh.ebo[i], 0, sizeof(Ohedo_IndexBuffer));
    }

    // Create VAO
    mesh.vao = Ohedo_CreateVertexArray();
    Ohedo_BindVertexArray(mesh.vao);

    cgltf_options options;
    memset(&options, 0, sizeof(cgltf_options));
    cgltf_data* data = 0;

    cgltf_call(cgltf_parse_file(&options, path, &data));
    cgltf_call(cgltf_load_buffers(&options, data, path));

    cgltf_scene* scene = data->scene;

    u32 primitiveCount = 0;

    foreach(nodeIndex, scene->nodes_count)
    {
        primitiveCount += count_cgltf_node_primitives(scene->nodes[nodeIndex]);
    }

    allocate_mesh(&mesh, primitiveCount);

    u32 primitiveIndex = 0;

    foreach(nodeIndex, scene->nodes_count)
    {
        process_cgltf_node(scene->nodes[nodeIndex], primitiveIndex, &mesh);
    }

    cgltf_free(data);

    for (i32 i = 0; i < mesh.num_ebos; i++)
    {
        Ohedo_BindVertexBuffer(mesh.vbo[i]);
        Ohedo_BindIndexBuffer(mesh.ebo[i]);
    }

    Ohedo_AddVertexAttribute(0, 3, sizeof(Ohedo_MeshVertex), 0, Ohedo_VertexAttributeType_Float);
    Ohedo_AddVertexAttribute(1, 3, sizeof(Ohedo_MeshVertex), offsetof(Ohedo_MeshVertex, position), Ohedo_VertexAttributeType_Float);
    Ohedo_AddVertexAttribute(2, 2, sizeof(Ohedo_MeshVertex), offsetof(Ohedo_MeshVertex, normal), Ohedo_VertexAttributeType_Float);

    Ohedo_UnbindVertexArray();

    return mesh;
}

Ohedo_Mesh Ohedo_CreateMeshFromRawData(Ohedo_MeshVertex* vertices, u32 vertexSize, void* indices, u32 indexSize)
{
    Ohedo_Mesh mesh;
    memset(&mesh, 0, sizeof(Ohedo_Mesh));
    return mesh; // TODO
}

void Ohedo_FreeMesh(Ohedo_Mesh mesh)
{
    foreach(i, array_count(mesh.vbo))
    {
        Ohedo_DeleteVertexBuffer(mesh.vbo[i]);
    }

    foreach(i, array_count(mesh.ebo))
    {
        Ohedo_DeleteIndexBuffer(mesh.ebo[i]);
    }

    Ohedo_DeleteVertexArray(mesh.vao);
}

void Ohedo_DrawMesh(Ohedo_Mesh mesh)
{
    Ohedo_BindVertexArray(mesh.vao);
    for (i32 i = 0; i < mesh.num_ebos; i++)
    {
        Ohedo_BindVertexBuffer(mesh.vbo[i]);
        Ohedo_BindIndexBuffer(mesh.ebo[i]);
        glDrawElements(GL_TRIANGLES, mesh.drawCounts[i], GL_UNSIGNED_INT, NULL);
        Ohedo_UnbindIndexBuffer();
        Ohedo_UnbindVertexBuffer();
    }
    Ohedo_UnbindVertexArray();
}
#include "Scene.h"
#include <assert.h>
#include <Ohedo/Graphics/BatchRenderer.h>
#include <glad/glad.h>
#include <stdio.h>

Ohedo_Scene* Ohedo_CreateScene()
{
    Ohedo_Scene* ptr = malloc(sizeof(Ohedo_Scene));
    ptr->entityCount = 0;
    return ptr;
}

void Ohedo_DestroyScene(Ohedo_Scene* scene)
{
    assert(scene);
    Ohedo_FreeAllEntitiesMemory(scene);
    free(scene);
}

Ohedo_Entity Ohedo_CreateEntity(Ohedo_Scene* scene)
{
    assert(scene);
    Ohedo_Entity entt = {0};
    entt.id = scene->entityCount;
    entt.transform = NULL;
    entt.spriteRenderer = NULL;
    entt.quadCollider = NULL;
    return entt; 
}

void Ohedo_AddEntity(Ohedo_Scene* scene, Ohedo_Entity* entity)
{
    scene->entities[scene->entityCount] = entity;
    scene->entityCount++;
}

void Ohedo_RemoveEntity(Ohedo_Scene* scene, Ohedo_Entity* entity)
{
    assert(scene);
    for (i32 i = 0; i < scene->entityCount; i++)
        if (entity->id == scene->entities[i]->id)
            scene->entities[i]->id = -1;
}

void Ohedo_RemoveAllEntities(Ohedo_Scene* scene)
{
    assert(scene);
    for (i32 i = 0; i < scene->entityCount; i++)
        scene->entities[i]->id = -1;
}

void Ohedo_FreeAllEntitiesMemory(Ohedo_Scene* scene)
{
    assert(scene);
    for (i32 i = 0; i < scene->entityCount; i++)
    {
        Ohedo_FreeEntityMemory(scene, scene->entities[i]);
    }
}

void Ohedo_FreeEntityMemory(Ohedo_Scene* scene, Ohedo_Entity* entity)
{
    assert(scene);
    if (entity)
    {
        Ohedo_RemoveQuadColliderComponent(entity);
        Ohedo_RemoveSpriteRendererComponent(entity);
        Ohedo_RemoveTransformComponent(entity);
    }
}

void Ohedo_UpdateScene(Ohedo_Scene* scene)
{  
    Ohedo_Mat4 camera = Ohedo_Mat4_Identity();

    for (i32 i = 0; i < scene->entityCount; i++)
    {
        Ohedo_Entity entt = *scene->entities[i];

        if (entt.camera && entt.camera->primary)
        {
            camera = entt.camera->pv_matrix;
        }
    }

    Ohedo_Batch_Begin(camera);

    for (i32 i = 0; i < scene->entityCount; i++)
    {
        Ohedo_Entity entt = *scene->entities[i];

        if (entt.transform)
        {
            if (entt.spriteRenderer)
            {
                Ohedo_Mat4 transform = Ohedo_Mat4_Identity();
                transform = Ohedo_Mat4_Multiply(transform, Ohedo_Mat4_Translate(entt.transform->position));
                transform = Ohedo_Mat4_Multiply(transform, Ohedo_Mat4_Scale(entt.transform->scale));
                // rotation
                transform = Ohedo_Mat4_Multiply(transform, Ohedo_Mat4_Rotate(Ohedo_Vec3_New(1.0f, 0.0f, 0.0f), entt.transform->rotation.x));
                transform = Ohedo_Mat4_Multiply(transform, Ohedo_Mat4_Rotate(Ohedo_Vec3_New(0.0f, 1.0f, 0.0f), entt.transform->rotation.y));
                transform = Ohedo_Mat4_Multiply(transform, Ohedo_Mat4_Rotate(Ohedo_Vec3_New(0.0f, 0.0f, 1.0f), entt.transform->rotation.z));

                if (glIsTexture(entt.spriteRenderer->texture.id))
                {
                    Ohedo_Batch_Draw_Textured_Quad_Mat4(transform, entt.spriteRenderer->color, entt.spriteRenderer->texture);
                }
                else
                {
                    Ohedo_Batch_Draw_Quad_Mat4(transform, entt.spriteRenderer->color);
                }
            }

            if (entt.quadCollider)
            {
                entt.quadCollider->x = entt.transform->position.x;
                entt.quadCollider->y = entt.transform->position.y;
                entt.quadCollider->width = entt.transform->scale.x;
                entt.quadCollider->height = entt.transform->scale.y;
            }
        }
    }

    Ohedo_Batch_End();
}
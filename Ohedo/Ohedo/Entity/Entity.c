#include "Entity.h"
#include <assert.h>

void Ohedo_AddTransformComponent(Ohedo_Entity* entity)
{
    entity->transform = malloc(sizeof(Ohedo_TransformComponent));
    entity->transform->position = Ohedo_Vec3_Identity();
    entity->transform->scale = Ohedo_Vec3_Scalar(1.0f);
    entity->transform->rotation = Ohedo_Vec3_Scalar(1.0f);
}

void Ohedo_AddSpriteRendererComponent(Ohedo_Entity* entity)
{
    entity->spriteRenderer = malloc(sizeof(Ohedo_SpriteRendererComponent));
    entity->spriteRenderer->color = Ohedo_Vec3_Identity();
}

void Ohedo_AddQuadColliderComponent(Ohedo_Entity* entity)
{
    entity->quadCollider = malloc(sizeof(Ohedo_QuadColliderComponent));

    if (entity->transform)
    {
        entity->quadCollider->x = entity->transform->position.x;
        entity->quadCollider->y = entity->transform->position.y;
        entity->quadCollider->width = entity->transform->scale.x;
        entity->quadCollider->height = entity->transform->scale.y;
    }
}

void Ohedo_RemoveTransformComponent(Ohedo_Entity* entity)
{
    if (entity->transform != NULL)
        free(entity->transform);
}

void Ohedo_RemoveSpriteRendererComponent(Ohedo_Entity* entity)
{
    if (entity->spriteRenderer != NULL)
        free(entity->spriteRenderer);
}

void Ohedo_RemoveQuadColliderComponent(Ohedo_Entity* entity)
{
    if (entity->quadCollider != NULL)
        free(entity->quadCollider);
}

i32 Ohedo_IsEntityValid(Ohedo_Entity* entity)
{
    return entity->id != -1;
}
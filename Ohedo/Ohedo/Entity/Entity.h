#ifndef OHEDO_ENTITY_H
#define OHEDO_ENTITY_H

#include <Ohedo/Entity/Components.h>

Ohedo_Define_Struct(Ohedo_Entity)
struct Ohedo_Entity
{
    u32 id;
    Ohedo_TransformComponent* transform;
    Ohedo_SpriteRendererComponent* spriteRenderer;
    Ohedo_QuadColliderComponent* quadCollider;
};

void Ohedo_AddTransformComponent(Ohedo_Entity* entity);
void Ohedo_AddSpriteRendererComponent(Ohedo_Entity* entity);
void Ohedo_AddQuadColliderComponent(Ohedo_Entity* entity);
void Ohedo_RemoveTransformComponent(Ohedo_Entity* entity);
void Ohedo_RemoveSpriteRendererComponent(Ohedo_Entity* entity);
void Ohedo_RemoveQuadColliderComponent(Ohedo_Entity* entity);
i32 Ohedo_IsEntityValid(Ohedo_Entity* entity);

#endif
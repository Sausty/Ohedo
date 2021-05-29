#ifndef OHEDO_SCENE_H
#define OHEDO_SCENE_H

#define OHEDO_MAX_ENTITIES 1000

#include <Ohedo/Entity/Entity.h>

Ohedo_Define_Struct(Ohedo_Scene)
struct Ohedo_Scene
{
    Ohedo_Entity* entities[OHEDO_MAX_ENTITIES];
    i32 entityCount;
};

Ohedo_Scene* Ohedo_CreateScene();
void Ohedo_DestroyScene(Ohedo_Scene* scene);

Ohedo_Entity Ohedo_CreateEntity(Ohedo_Scene* scene);
void Ohedo_AddEntity(Ohedo_Scene* scene, Ohedo_Entity* entity);
void Ohedo_RemoveEntity(Ohedo_Scene* scene, Ohedo_Entity* entity);
void Ohedo_RemoveAllEntities(Ohedo_Scene* scene);
void Ohedo_FreeAllEntitiesMemory(Ohedo_Scene* scene);
void Ohedo_FreeEntityMemory(Ohedo_Scene* scene, Ohedo_Entity* entity);

void Ohedo_UpdateScene(Ohedo_Scene* scene);

#endif
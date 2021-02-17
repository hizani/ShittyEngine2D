#include "./EntityManager.h"
#include "./Collision.h"
#include "./components/ColliderComponent.h"
#include "iostream"
void EntityManager::ClearData()
{
    for (auto &entity : entities)
    {
        entity->Destroy();
    }
}

bool EntityManager::HasNoEntities()
{
    return entities.size() == 0;
}

void EntityManager::Update(float deltaTime)
{
    for (auto &entity : entities)
    {
        entity->Update(deltaTime);
    }
    DestroyInactiveEntities();
}

void EntityManager::DestroyInactiveEntities(){
    /*
    for (int i= 0; i < entities.size(); i++){
        if(entities[i]->IsActive()){
            entities.erase(entities.begin() + i);
        }
    }
    */
}

void EntityManager::Render()
{
    for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++)
    {
        for (auto &entity : GetEntitiesByLayer(static_cast<LayerType>(layerNumber)))
        {
            entity->Render();
        }
    }

    /*for(auto& entity: entities){
        entity->Render();
    }*/
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer, int posX, int posY, int velX, int velY, int w, int h, int s)
{
    Entity* entity = new Entity(*this, entityName, layer, posX, posY, velX, velY, w, h, s);
    entities.emplace_back(entity);
    return* entity;
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer)
{
    Entity* entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity);
    return* entity;
}

std::vector<Entity*> EntityManager::GetEntities() const
{
    return entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const
{
    std::vector<Entity*> selectedEntities;
    for (auto& entity : entities)
    {
        if (entity->layer == layer)
        {
            selectedEntities.emplace_back(entity);
        }
    }
    return selectedEntities;
}

Entity *EntityManager::GetPlayer() const
{
    //Поиск сущности на слое игрока
    for (auto &entity : entities)
    {
        if (entity->layer == PLYAER_LAYER)
        {
            return entity;
        }
    }
    return nullptr;
}

unsigned int EntityManager::GetEntityCount()
{
    return entities.size();
}

CollisionType EntityManager::CheckCollisions() const
{
    //Проход по всем сущностям
    for (int i = 0; i < entities.size() - 1; i++)
    {
        auto &thisEntity = entities[i];
        if (thisEntity->HasComponent<ColliderComponent>())
        {
            ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();
            //Сравнение сущности с другими сущностями
            for (int j = i + 1; j < entities.size(); j++)
            {
                auto &thatEntity = entities[j];
                if (thisEntity->name.compare(thatEntity->name) != 0 && thatEntity->HasComponent<ColliderComponent>())
                {
                    ColliderComponent* thatCollider = thatEntity->GetComponent<ColliderComponent>();
                    //Если коллизия произошла, возвращаем тип коллизии
                    if (Collision::CheckRectangleCollision(thisCollider->collider, thatCollider->collider))
                    {
                    std::cout << "Collision occurred" << std::endl;
                        if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("ENEMY") == 0)
                        {
                            return PLAYER_ENEMY_COLLISION;
                        }
                        if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("PROJECTILE") == 0)
                        {
                            return PLAYER_PROJECTILE_COLLISION;
                        }
                        if (thisCollider->colliderTag.compare("ENEMY") == 0 && thatCollider->colliderTag.compare("FRIENDLY_PROJECTILE") == 0)
                        {
                            return ENEMY_PROJECTILE_COLLISION;
                        }
                        if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("LEVEL_COMPLETE") == 0)
                        {
                            return PLAYER_LEVEL_COMPLETE_COLLISION;
                        }
                    }
                }
            }
        }
    }
    return NO_COLLISION;
}

/*
std::string EntityManager::CheckEntityCollisions(Entity& checkedEntity) const
{
    ColliderComponent *checkedCollider = checkedEntity.GetComponent<ColliderComponent>();
    for (auto& entity : entities)
    {
        if (entity->name.compare(checkedEntity.name) == 0 || entity->name.compare("Tile") == 0)
            continue;

        if (entity->HasComponent<ColliderComponent>())
        {
            ColliderComponent *otherCollider = entity->GetComponent<ColliderComponent>();
            if (Collision::CheckRectangleCollision(checkedCollider->collider, otherCollider->collider))
            {
                return otherCollider->colliderTag;
            }
        }
    }
    return std::string();
}
*/
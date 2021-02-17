#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include "./Entity.h"
#include "./Component.h"

class EntityManager
{
private:
    std::vector<Entity *> entities; // Список сущностей
public:
    Entity& AddEntity(std::string entityName, LayerType layer);
    Entity& AddEntity(std::string entityName, LayerType layer, int posX, int posY, int velX, int velY, int w, int h, int s);
    //Получение указателя на игрока
    Entity* GetPlayer() const;
    //Уничтожение сущностей
    void ClearData();             
    void Update(float deltaTime);
    void Render();               
    bool HasNoEntities();        
    //Получение списка сущностей
    std::vector<Entity*> GetEntities() const; 
    //Получение сущностей по слою
    std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
    //Получение кол-ва сущностей
    unsigned int GetEntityCount();
    //Проверка коллизий
    CollisionType CheckCollisions() const;
    //Уничтожение неактивных сщуностей
    void DestroyInactiveEntities();
};

#endif
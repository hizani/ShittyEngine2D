#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <map>
#include "./Constants.h"
#include "./Component.h"
#include "components/TransformComponent.h"
class EntityManager;

class Entity
{
private:
    EntityManager &manager;                                         //EntityManager к которому принадлежит сущность
    bool isActive;                              
    std::vector<Component *> components;                            //Список компонентов сущности
    std::map<const std::type_info *, Component *> componentTypeMap; //Список компонентов

public:
    std::string name;
    LayerType layer;
    Entity(EntityManager &manager, std::string name, LayerType layer);
    Entity(EntityManager &manager, std::string name, LayerType layer, int posX, int posY, int velX, int velY, int w, int h, int s);
    void Update(float deltaTime);
    void Render();
    void Destroy();
    //Проверка активности сущности
    bool IsActive() const;

    //Добавление компонента
    template <typename T, typename... TArgs>
    T& AddComponent(TArgs &&... args)
    {
        //Вызов конструктора компонента
        T* newComponent(new T(std::forward<TArgs>(args)...));
        //Присвоение компоненту родителя
        newComponent->owner = this;
        //Добавление указателя на компонент в список компонентов
        components.emplace_back(newComponent);
        componentTypeMap[&typeid(*newComponent)] = newComponent;
        //Вызов инициализации компонента
        newComponent->Initialize();
        return* newComponent;
    }
    //Получение компонента по названию
    template <typename T>
    T* GetComponent()
    {
        return static_cast<T*>(componentTypeMap[&typeid(T)]);
    }
    
    //Проверка наличия компонента
    template <typename T>
    bool HasComponent()
    {
        auto search = componentTypeMap.find(&typeid(T));
        if (search != componentTypeMap.end())
            return true;
        else
            return false;
    }
};

#endif
#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component
{
public:
    Entity *owner; //Владелец компонента
    //TODO: Доделать диструкторы
    //virtual ~Component() = 0;
    //Инициализация компонента
    virtual void Initialize() = 0; 
    //Обновление компонента
    virtual void Update(float deltaTime) = 0; 
    //Рендер компонента
    virtual void Render() = 0; 
};

#endif
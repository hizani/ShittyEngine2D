#include "./Entity.h"

Entity::Entity(EntityManager &manager, std::string name, LayerType layer) : manager(manager), name(name), layer(layer)
{
    this->isActive = true;
}

Entity::Entity(EntityManager &manager, std::string name, LayerType layer, int posX, int posY, int velX, int velY, int w, int h, int s) : manager(manager), name(name), layer(layer)
{
    this->AddComponent<TransformComponent>(posX, posY, velX, velY, w, h, s);
    this->isActive = true;
}

void Entity::Update(float deltaTime)
{
    for (auto &component : components)
    {
        component->Update(deltaTime);
    }
}

void Entity::Render()
{
    for (auto &component : components)
    {
        component->Render();
    }
}

void Entity::Destroy()
{
    this->isActive = false;
}

bool Entity::IsActive() const
{
    return this->isActive;
}

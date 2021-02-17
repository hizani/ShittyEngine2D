#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../EntityManager.h"
#include "../../lib/glm/glm.hpp"
#include "../Game.h"
#include <SDL2/SDL.h>

class TransformComponent : public Component
{
private:
    void PositionCheck();

public:
    glm::vec2 position; //Позиция сущности в XY координатах
    glm::vec2 velocity; //Скорость сущности в XY координатах
    int width;          //Ширина сущности
    int height;         //Высота сущности
    float scale;        //множитель размера сущности

    TransformComponent(int posX, int posY, int velX, int velY, int w, int h, float s);
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;
};

#endif
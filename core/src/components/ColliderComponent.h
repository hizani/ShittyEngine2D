#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <SDL2/SDL.h>
#include "../Game.h"
#include "../EntityManager.h"
#include "TransformComponent.h"

class ColliderComponent : public Component
{
private:
    bool isRendered;
    int clampValue;
public:
    std::string colliderTag;
    SDL_Rect collider;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    TransformComponent *transform;

    ColliderComponent(std::string colliderTag, int x, int y, int width, int height, int clampValue, bool isRendered);
    ColliderComponent(std::string colliderTag, int x, int y, int width, int height, int clampValue);

    void Initialize() override;

    void Update(float deltaTime) override;

    void Render() override;
};

#endif
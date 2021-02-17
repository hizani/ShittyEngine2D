#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(std::string colliderTag, int x, int y, int width, int height, int clampValue, bool isRendered) : isRendered(isRendered), clampValue(clampValue)
{
    this->colliderTag = colliderTag;
    this->collider = {x, y, width, height};

}
ColliderComponent::ColliderComponent(std::string colliderTag, int x, int y, int width, int height, int clampValue)
{
    isRendered = false;
    this->colliderTag = colliderTag;
    this->collider = {x, y, width, height};
}

void ColliderComponent::Initialize()
{
    transform = owner->GetComponent<TransformComponent>();
    collider.w /= clampValue;
    collider.h /= clampValue;
    collider.w *= transform->scale;
    collider.h *= transform->scale;
    sourceRectangle = {0, 0, transform->width, transform->height};
    destinationRectangle = {collider.x, collider.y, collider.w, collider.h};
}

void ColliderComponent::Update(float deltaTime)
{
    int startWidth = collider.w * clampValue;
    int startHeight = collider.h * clampValue;
    collider.x = static_cast<int>(transform->position.x) + (startWidth/2 - collider.w/2) - (Game::camera.x);;
    collider.y = static_cast<int>(transform->position.y) + (startHeight/2 - collider.h/2) - (Game::camera.y);;
    destinationRectangle.x = collider.x - Game::camera.x;
    destinationRectangle.y = collider.y - Game::camera.y;
}

void ColliderComponent::Render()
{
    if (isRendered)
        SDL_RenderDrawRect(Game::renderer, &collider);
}
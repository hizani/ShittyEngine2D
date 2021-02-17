#include "./TransformComponent.h"
#include "../Constants.h"
TransformComponent::TransformComponent(int posX, int posY, int velX, int velY, int w, int h, float s)
{
    position = glm::vec2(posX, posY);
    velocity = glm::vec2(velX, velY);
    width = w;
    height = h;
    scale = s;
}

void TransformComponent::PositionCheck()
{
    if (this->position.x <= 0)
        position.x = 0;
    if (this->position.y <= 0)
        position.y = 0;
    /*
    if (this->position.x >= WINDOW_WIDTH - width * scale)
        position.x = WINDOW_WIDTH - width * scale;
    if (this->position.y >= WINDOW_HEIGHT - height * scale)
        position.y = WINDOW_HEIGHT - height * scale;
    */
}

void TransformComponent::Initialize()
{
}

void TransformComponent::Update(float deltaTime)
{
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    PositionCheck();
}

void TransformComponent::Render()
{
}

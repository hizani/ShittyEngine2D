#include "ProjectileEmitterComponent.h"

ProjectileEmitterComponent::ProjectileEmitterComponent(int speed, int angleDeg, int range, bool isRepeatable){
    this->speed = speed;
    this->range = range;
    this->isRepeatable = isRepeatable;
    this->angleRad = glm::radians(static_cast<float>(angleDeg));
}

void ProjectileEmitterComponent::Initialize() {
    transform = owner->GetComponent<TransformComponent>();
    origin = glm::vec2(transform->position.x, transform->position.y);
    /* 
    чтобы узнать скорость по x нужно косинус вектора от оси умножить на скорость
    по y - синус вектора от оси на скорость
    */
    transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed);
}

void ProjectileEmitterComponent::Update(float deltaTime) {
    if(glm::distance(transform->position, origin) > range) { 
        if(isRepeatable){
            transform->position.x = origin.x;
            transform->position.y = origin.y;
        } else {
            owner->Destroy();
        }
    }
}

void ProjectileEmitterComponent::Render()
{
    
}
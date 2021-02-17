#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include "../../lib/glm/glm.hpp"
#include "../EntityManager.h"
#include "./TransformComponent.h"

class ProjectileEmitterComponent : public Component {
    private:
        TransformComponent* transform;
        glm::vec2 origin;   //Местоположение родительской сущности
        int speed;
        int range;
        float angleRad;     //Угл полета
        bool isRepeatable;
    public:
        ProjectileEmitterComponent(int speed, int angle, int rangeDeg, bool isRepeatable);

        void Initialize() override;
        void Update(float deltaTime) override;
        void Render() override;
};

#endif
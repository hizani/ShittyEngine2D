#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(unsigned int index, unsigned int frameCount, unsigned int animationSpeed)
{
    this->index = index;
    this->frameCount = frameCount;
    this->animationSpeed = animationSpeed;
}
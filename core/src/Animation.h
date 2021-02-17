#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>

class Animation
{
public:
    unsigned int index;             //Индекс анимации
    unsigned int frameCount;        //Количество кадров
    unsigned int animationSpeed;    //Скорость анимации
    Animation();
    Animation(unsigned int index, unsigned int frameCount, unsigned int animationSpeed);
};

#endif
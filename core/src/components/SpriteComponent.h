#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "./TransformComponent.h"
#include "../Animation.h"
#include <vector>
#include <string>

class SpriteComponent : public Component
{
private:
    TransformComponent *transformComponent; //TransformComponent родительского объекта
    SDL_Texture *texture;                   //Текстура
    SDL_Rect sourceRectangle;               //Источник
    SDL_Rect destinationRectangle;          //координаты перемещения текстуры
    bool isAnimated;             
    int numFrames;
    int animationSpeed;
    bool isFixed;
    std::map<std::string, Animation> animations;
    std::string currentAnimationName;
    unsigned int animationIndex = 0;

public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
    SpriteComponent(std::string assetTextureId);
    SpriteComponent(std::string assetTextureId, bool isFixed);
    SpriteComponent(std::string asetTextureId, std::map<std::string, Animation> animations, bool isFixed);
    void SetTexture(std::string assetTextureId);
    void Play(std::string animationIndex);
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;
};

#endif
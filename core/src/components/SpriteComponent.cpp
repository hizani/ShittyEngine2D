#include "SpriteComponent.h"

void SpriteComponent::Play(std::string animationName)
{
    numFrames = animations[animationName].frameCount;
    animationIndex = animations[animationName].index;
    animationSpeed = animations[animationName].animationSpeed;
    currentAnimationName = animationName;
}

void SpriteComponent::SetTexture(std::string assetTextureId)
{
    texture = Game::assetManager->GetTexture(assetTextureId);
}

SpriteComponent::SpriteComponent(std::string assetTextureId)
{
    isAnimated = false;
    isFixed = false;
    SetTexture(assetTextureId);
}

SpriteComponent::SpriteComponent(std::string assetTextureId, bool isFixed)
{
    this->isAnimated = false;
    this->isFixed = isFixed;
    SetTexture(assetTextureId);
}

SpriteComponent::SpriteComponent(std::string asetTextureId, std::map<std::string, Animation> animations, bool isFixed)
{
    this->isAnimated = true;
    this->isFixed = isFixed;
    this->animations = animations;

    this->animationIndex = 0;
    this->currentAnimationName = "DownIdle";
    Play(this->currentAnimationName);

    SetTexture(asetTextureId);
}

void SpriteComponent::Initialize()
{
    transformComponent = owner->GetComponent<TransformComponent>();
    sourceRectangle.x = 0;
    sourceRectangle.y = 0;
    sourceRectangle.w = transformComponent->width;
    sourceRectangle.h = transformComponent->height;
}

void SpriteComponent::Update(float deltaTime)
{
    if (isAnimated)
    {
        /*формула вычисления прохождения цикла анимации. Если остаток от numFrames будет равен или меньше нуля, то анимация начнется заново. */
        sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
    }
    sourceRectangle.y = animationIndex * transformComponent->height;
    
    destinationRectangle.x = static_cast<int>(transformComponent->position.x) - (isFixed ? 0 : Game::camera.x);
    destinationRectangle.y = static_cast<int>(transformComponent->position.y) - (isFixed ? 0 : Game::camera.y);
    destinationRectangle.w = transformComponent->width * transformComponent->scale;
    destinationRectangle.h = transformComponent->height * transformComponent->scale;
}

void SpriteComponent::Render()
{
    TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
}
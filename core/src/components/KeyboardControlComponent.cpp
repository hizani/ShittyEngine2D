#include "KeyboardControlComponent.h"

// возврат кода клавиши SDL
std::string GetSDLKeyStringCode(std::string key)
{
    if (key.compare("up") == 0)
        return "1073741906";
    if (key.compare("down") == 0)
        return "1073741905";
    if (key.compare("left") == 0)
        return "1073741904";
    if (key.compare("right") == 0)
        return "1073741903";
    if (key.compare("space") == 0)
        return "32";
    return std::to_string(static_cast<int>(key[0]));
}

KeyboardControlComponent::KeyboardControlComponent(std::string upKey, std::string downKey, std::string rightKey, std::string leftKey, std::string shootKey)
{
    this->upKey = GetSDLKeyStringCode(upKey);
    this->downKey = GetSDLKeyStringCode(downKey);
    this->rightKey = GetSDLKeyStringCode(rightKey);
    this->leftKey = GetSDLKeyStringCode(leftKey);
    this->shootKey = GetSDLKeyStringCode(shootKey);
}

void KeyboardControlComponent::Initialize()
{

    transformComponent = owner->GetComponent<TransformComponent>();
    spriteComponent = owner->GetComponent<SpriteComponent>();
}

void KeyboardControlComponent::Update(float deltaTime)
{
    if (Game::event.type == SDL_KEYDOWN)
    {
        std::string keyCode = std::to_string(Game::event.key.keysym.sym);
        if (keyCode.compare(upKey) == 0)
        {
            transformComponent->velocity.y = -20;
            transformComponent->velocity.x = 0;
            spriteComponent->Play("UpAnimation");
        }
        if (keyCode.compare(rightKey) == 0)
        {
            transformComponent->velocity.y = 0;
            transformComponent->velocity.x = 20;
            spriteComponent->Play("RightAnimation");
        }
        if (keyCode.compare(downKey) == 0)
        {
            transformComponent->velocity.y = 20;
            transformComponent->velocity.x = 0;
            spriteComponent->Play("DownAnimation");
        }
        if (keyCode.compare(leftKey) == 0)
        {
            transformComponent->velocity.y = 0;
            transformComponent->velocity.x = -20;
            spriteComponent->Play("LeftAnimation");
        }
        if (keyCode.compare(shootKey) == 0)
        {
        }
    }

    if (Game::event.type == SDL_KEYUP)
    {
        std::string keyCode = std::to_string(Game::event.key.keysym.sym);
        if (keyCode.compare(upKey) == 0)
        {
            transformComponent->velocity.y = 0;
            spriteComponent->Play("UpIdle");
        }
        if (keyCode.compare(rightKey) == 0)
        {
            transformComponent->velocity.x = 0;
            spriteComponent->Play("RightIdle");
        }
        if (keyCode.compare(downKey) == 0)
        {
            transformComponent->velocity.y = 0;
            spriteComponent->Play("DownIdle");
        }
        if (keyCode.compare(leftKey) == 0)
        {
            transformComponent->velocity.x = 0;
            spriteComponent->Play("LeftIdle");
        }
        if (keyCode.compare(shootKey) == 0)
        {
        }
    }
}

void KeyboardControlComponent::Render()
{
}
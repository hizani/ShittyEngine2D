#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "../FontManager.h"
#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../Game.h"

class TextComponent : public Component
{
private:
    SDL_Rect position;      //Положение текста
    std::string text;       //Текст
    std::string fontFamily; //Шрифт
    SDL_Color color;        //Цвет
    SDL_Texture *texture;   //Текстура

public:
    TextComponent(int x, int y, std::string text, std::string fontFamily, const SDL_Color color);
    //Преобразование текста в текстуру
    void SetText(std::string text, std::string fontFamily);

    void Initialize() override {};
    void Update(float deltaTime) override{};
    void Render() override;
};

#endif
#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "Game.h"

class FontManager
{
public:
        //Загрузка шрифта в память программы
        static TTF_Font* LoadFont(const char *fileName, int fontSize); 
        //Отрисовка шрифта
        static void Draw(SDL_Texture *texture, SDL_Rect position);     
};

#endif
#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "TextureManager.h"
#include "FontManager.h"
#include "EntityManager.h"

//Класс для управления загруженными текстурами
class AssetManager
{
private:
    EntityManager* manager;
    std::map<std::string, SDL_Texture*> textures;   // map со всеми текстурами, которые использует игра
    std::map<std::string, TTF_Font*> fonts;         // map со всеми шрифтами, которые использует игра
public:
    AssetManager(EntityManager *manager);
    ~AssetManager();
    //Очистка данных 
    void ClearData();                                                         
    //Добавление текстуры в textures
    void AddTexture(std::string textureId, const char *filePath);           
    //Получение текстуры из texutres
    SDL_Texture* GetTexture(std::string textureId);                         

    //Добавление шрифта в fonts  
    void AddFont(std::string fontId, const char *filePath, int fontSize);   
     //Получение шрифта из fonts
    TTF_Font* GetFont(std::string fontId);                                 
};

#endif
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../lib/lua/sol.hpp"
#include "./Entity.h"
#include "./Component.h"
#include "./EntityManager.h"
#include "components/TransformComponent.h"

extern "C"
{
#include "../lib/lua/lua.h"
#include "../lib/lua/lualib.h"
#include "../lib/lua/lauxlib.h"
}


class AssetManager;

class Game
{
private:
    bool isRunning;
    SDL_Window* window;

public:
    Game();
    ~Game();
    int lastFrameTicks;
    bool IsRunning() const;
    static SDL_Renderer* renderer;
    static AssetManager* assetManager;
    static SDL_Event event;                 //Класс, содержащий структуры для разных событий
    static SDL_Rect camera;
    void LoadScene(int levelNumber);        //Загрузка компонентов игровой сцены из файла скрипта
    void Initialize(int width, int height); //Инициализация библиотеки SDL и ее компонентов
    void ProcessInput();                    //Обработка ввода
    void Update();                          //Обновление состояния игры
    void Render();                          //Отрисовка всех сущностей игры
    void Destroy();
    void HandleCameraMovement();
    void CheckCollisions();
    void GameOver();
    void NextLevel();
};

#endif
#include <iostream>
#include "../lib/glm/glm.hpp"
#include "./Constants.h"
#include "./Game.h"
#include "./AssetManager.h"
#include "./Map.h"
#include "components/SpriteComponent.h"
#include "components/KeyboardControlComponent.h"
#include "components/ColliderComponent.h"
#include "components/TextComponent.h"
#include "components/ProjectileEmitterComponent.h"

EntityManager manager;
AssetManager *Game::assetManager = new AssetManager(&manager);
SDL_Renderer *Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map *map;

Game::Game()
{
    this->isRunning = false;
}

Game::~Game()
{
}

//Функция проверки состаяния игры
bool Game::IsRunning() const
{
    return this->isRunning;
}

//Инициализация SDL элементов
void Game::Initialize(int width, int height)
{
    //Инициализация всех элементов SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    //Инициализация элемента обработки шрифтов
    if (TTF_Init() != 0)
    {
        std::cerr << "Error initializing SDL TTF" << std::endl;
        return;
    }
    //Задание параметров создаваемого окна
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        std::cerr << "SDL window error" << std::endl;
        return;
    }
    /*
    создание рендерщика, который принимает окно для отрисовки, 
    драйвер (по умолчанию -1) 
    и флаг (я так и не понял зачем он и поэтому ничего не указывал)
    */
    renderer = SDL_CreateRenderer(window, -1, 0); 
    if (!renderer)
    {
        std::cerr << "SDL Renderer error" << std::endl;
        return;
    }

    LoadScene(1);

    isRunning = true;
    return;
}

void Game::LoadScene(int levelNumber)
{
    //Инициализация компонентов для работы с lua
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
    std::string levelName = "Level" + std::to_string(levelNumber);
    lua.script_file("./assets/scripts/" + levelName + ".lua");

    /* 
        Следующий далее повторяющийся код, который содержит что-то вроде:
            sol::optional<sol::table> optionalIndex = levelAssets[assetIndex]
            if(optionalIndex = sol::nullptr) {...} else {...}
        Предназначен для проверки наличия указанной таблицы в скрипте
    */


    sol::table levelData = lua[levelName];
     //////////////////////////////////////////////////////
    // ЗАГРУЗКА АССЕТОВ ИЗ КОНФИГУРАЦИОННОГО ФАЙЛА LUA  // 
   //////////////////////////////////////////////////////
    sol::table levelAssets = levelData["assets"];
    unsigned int assetIndex = 0;
    while (true)
    {
        sol::optional<sol::table> optionalIndex = levelAssets[assetIndex];
        if (optionalIndex == sol::nullopt)
        {
            break;
        }
        else
        {
            sol::table asset = levelAssets[assetIndex];
            std::string assetType = asset["type"];
            //Загрузка текстуры
            if(assetType.compare("texture") == 0)
            {
                std::string assetId = asset["id"];
                std::string assetFile = asset["file"];
                assetManager->AddTexture(assetId, assetFile.c_str());
            }
            //Загрузка шрифта
            if(assetType.compare("font") == 0)
            {
                std::string assetId = asset["id"];
                std::string assetFile = asset["file"];
                int fontSize = asset["fontSize"];
                assetManager->AddFont(assetId, assetFile.c_str(), fontSize);
            }
        }
        assetIndex++;
    }
     //////////////////////////////////////////////////////
    // ЗАГРУЗКА КАРТЫ ИЗ КОНФИГУРАЦИОННОГО ФАЙЛА LUA    //
   //////////////////////////////////////////////////////
   sol::table levelMap = levelData["map"];

   map = new Map(
       levelMap["textureAssetId"],
       static_cast<int>(levelMap["scale"]),
       static_cast<int>(levelMap["tileSize"])
   );
    
    map->LoadMap(
        levelMap["file"],
        static_cast<int>(levelMap["mapSizeX"]),
        static_cast<int>(levelMap["mapSizeY"])
    );
     //////////////////////////////////////////////////////
    // ЗАГРУЗКА СУЩНОСТЕЙ ИЗ КОНФИГУРАЦИОННОГО ФАЙЛА LUA//
   //////////////////////////////////////////////////////
   sol::table levelEntities = levelData["entities"];
    unsigned int entityIndex = 0;
    while (true)
    {
        sol::optional<sol::table> optionalIndex = levelEntities[entityIndex];
        if (optionalIndex == sol::nullopt)
        {
            break;
        }
        else
        {
            sol::table entity = levelEntities[entityIndex];
            std::string entityName = entity["name"];
            LayerType entityLayerType = static_cast<LayerType>(static_cast<int>(entity["layer"]));
            
            //Добавление новой сущности
            auto &newEntity(manager.AddEntity(
                entityName, entityLayerType,
                static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                static_cast<int>(entity["components"]["transform"]["velocity"]["x"]),
                static_cast<int>(entity["components"]["transform"]["velocity"]["y"]),
                static_cast<int>(entity["components"]["transform"]["width"]),
                static_cast<int>(entity["components"]["transform"]["height"]),
                static_cast<int>(entity["components"]["transform"]["scale"])));
            
            //Добавление SpriteComponent
            sol::optional<sol::table> optionalSpriteComponent = entity["components"]["sprite"];
            if (optionalSpriteComponent != sol::nullopt)
            {
                sol::optional<sol::table> isAnimated = entity["components"]["sprite"]["animationInfo"];
                if(isAnimated != sol::nullopt)
                {
                    std::map<std::string, Animation> entityAnimation;
                    unsigned int animationCount = 0;
                    while (true)
                    {
                        sol::optional<sol::table> optionalAnimation = entity["components"]["sprite"]["animationInfo"][animationCount];
                        if (optionalAnimation == sol::nullopt)
                        {
                            break;
                        }
                        else
                        {
                            entityAnimation.emplace(
                                std::pair<std::string, Animation>{
                                entity["components"]["sprite"]["animationInfo"][animationCount]["name"],
                                Animation(animationCount,
                                static_cast<int>(entity["components"]["sprite"]["animationInfo"][animationCount]["frameCount"]),
                                static_cast<int>(entity["components"]["sprite"]["animationInfo"][animationCount]["animationSpeed"])
                                )}
                            );
                        }
                        animationCount++;
                    }
                    newEntity.AddComponent<SpriteComponent>(
                        entity["components"]["sprite"]["textureAssetId"],
                        entityAnimation,
                        entity["components"]["sprite"]["fixed"]);
                }
                else if(isAnimated == sol::nullopt && entity["components"]["sprite"]["fixed"] == true)
                {
                    newEntity.AddComponent<SpriteComponent>(
                        entity["components"]["sprite"]["textureAssetId"],
                        true);
                }
                else
                {
                    newEntity.AddComponent<SpriteComponent>(static_cast<std::string>(entity["components"]["sprite"]["textureAssetId"]));
                }
            }

            //Добавление ColliderComponent
            sol::optional<sol::table> optionalColliderComponent = entity["components"]["collider"];
            if (optionalColliderComponent != sol::nullopt)
            {
               int colliderWidth = static_cast<int>(entity["components"]["transform"]["width"]); 
               int colliderHeight = static_cast<int>(entity["components"]["transform"]["height"]);
               int colliderXPos = static_cast<int>(entity["components"]["transform"]["position"]["x"]);
               int colliderYPos = static_cast<int>(entity["components"]["transform"]["position"]["y"]);
               int clampValue = static_cast<int>(entity["components"]["collider"]["clampValue"]);

                newEntity.AddComponent<ColliderComponent>(
                    entity["components"]["collider"]["tag"],
                    colliderXPos,
                    colliderYPos,
                    colliderWidth,
                    colliderHeight,
                    clampValue,
                    entity["components"]["collider"]["isRendered"]
                );
            }

            //Добавление Input компонентов
            sol::optional<sol::table> optionaIinputComponents = entity["components"]["input"];
            if (optionaIinputComponents != sol::nullopt)
            {
                sol::optional<sol::table> optionaKeyboardComponent = entity["components"]["input"]["keyboard"];
                if(optionaKeyboardComponent != sol::nullopt)
                {
                    newEntity.AddComponent<KeyboardControlComponent>(
                        entity["components"]["input"]["keyboard"]["up"],
                        entity["components"]["input"]["keyboard"]["down"],
                        entity["components"]["input"]["keyboard"]["right"],
                        entity["components"]["input"]["keyboard"]["left"],
                        entity["components"]["input"]["keyboard"]["shoot"]);
                }
            }

            //Добавление ProjectileEmitterComponent
            sol::optional<sol::table> optionaProjectileEmiterComponents = entity["components"]["projectileEmitter"];
            if (optionaProjectileEmiterComponents != sol::nullopt)
            {   
                int parentEntityXPos = entity["components"]["transform"]["position"]["x"];
                int parentEntityYPos = entity["components"]["transform"]["position"]["y"];
                int parentEntityWidth = entity["components"]["transform"]["width"];
                int parentEntityHeight = entity["components"]["transform"]["height"];
                int projectileWidth = entity["components"]["projectileEmitter"]["width"];
                int projectileHeight = entity["components"]["projectileEmitter"]["height"];
                float projectileScale = static_cast<float>(entity["components"]["projectileEmitter"]["scale"]);
                int projectileSpeed = entity["components"]["projectileEmitter"]["speed"];
                int projectileRange = entity["components"]["projectileEmitter"]["range"];
                int projectileAngle = entity["components"]["projectileEmitter"]["angle"];
                bool projectileShouldLoop = entity["components"]["projectileEmitter"]["shouldLoop"];
                std::string textureAssetId = entity["components"]["projectileEmitter"]["textureAssetId"];
                
                Entity& projectile(manager.AddEntity("projectile", PROJECTILE_LAYER));
                projectile.AddComponent<TransformComponent>(
                    parentEntityXPos +  (parentEntityWidth / 2),
                    parentEntityYPos + (parentEntityHeight / 2),
                    0,
                    0,
                    projectileWidth,
                    projectileHeight,
                    projectileScale
                );
                projectile.AddComponent<SpriteComponent>(textureAssetId);
                projectile.AddComponent<ProjectileEmitterComponent>(
                    projectileSpeed,
                    projectileAngle,
                    projectileRange,
                    projectileShouldLoop
                );
                projectile.AddComponent<ColliderComponent>(
                    "PROJECTILE",
                    parentEntityXPos,
                    parentEntityYPos,
                    projectileWidth,
                    projectileHeight,
                    entity["components"]["collider"]["clampValue"],
                    entity["components"]["collider"]["isRendered"]
                );
            }
             //Добавление TextComponent
            sol::optional<sol::table> optionalTextComponents = entity["components"]["label"];
            if (optionalTextComponents != sol::nullopt)
            {   
                newEntity.AddComponent<TextComponent>(
                    entity["components"]["label"]["posX"],
                    entity["components"]["label"]["posY"],
                    entity["components"]["label"]["text"],
                    entity["components"]["label"]["font"],
                    SDL_Color{255,255,255,255}
                );
            }
        }
        entityIndex++;
    }
}

//Обработка ввода
void Game::ProcessInput()
{
    //проверка наличия ожидаемых событий (нажатия клавиш, мыши и т.д.)
    SDL_PollEvent(&event); 
    switch (event.type)
    {
    case SDL_QUIT:
    {
        isRunning = false;
        break;
    }
    /*
        проверка соответствует  ли нажатая клавиша клавише ESC при срабатывании события нажатия клавиши
        (key отвечает за события нажатия клавиш, струкрута keysym содержит информацию о событии, sym содержит конкретную нажатую клавишу)
        */
    case SDL_KEYDOWN:
    {
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            isRunning = false;
            break;
        }
    }
    default:
    {
        break;
    }
    }
}

void Game::Update()
{
    //Ждать пока не пройдет 1000/FPS млсек с предыдущего кадра(установка FPS)
    //Ожидание пока не пройдет 1000/FPS млсек с предыдущего кадра(установка FPS). Время смены кадра минус разница во времени между текущим временем и прошлым кадром
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTicks); 
    //Если разница отрицательна то ждать не нужно
    if (timeToWait > 0)
        SDL_Delay(timeToWait);

    float deltaTime = (SDL_GetTicks() - lastFrameTicks) / 1000.0f;  //разница по времени между текущим и предыдущим кадром
    // установка максимального deltaTime чтоб если зафризит, то ничего бы не улетало
    deltaTime = deltaTime > 0.05f ? 0.05f : deltaTime;

    lastFrameTicks = SDL_GetTicks(); //устанавливает милисекунды для текущего кадра

    manager.Update(deltaTime); //запуск обработки сущностей

    HandleCameraMovement();

    CheckCollisions();
}

void Game::Render()
{
    //задает цвет, которым будет рисовать рендерер
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255); 
    //очищает содержимое рендерера
    SDL_RenderClear(renderer);                         
    //проверка на наличие сущностей
    switch (manager.GetEntityCount()) 
    {
    case 0:
        return;
    default:
        break;
    }

    manager.Render(); //отрисовка сущностей

    SDL_RenderPresent(renderer); //отрисовываем содержимое рендерера
}

void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::HandleCameraMovement()
{
    //Получение местоположения игрока
    TransformComponent *playerTransform = manager.GetPlayer()->GetComponent<TransformComponent>();

    //Нахождение игрока в центре экрана
    camera.x = playerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = playerTransform->position.y - (WINDOW_HEIGHT / 2);

    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::CheckCollisions()
{
    CollisionType collisionType = manager.CheckCollisions();
    if (collisionType == PLAYER_ENEMY_COLLISION)
    {
        GameOver();
    }
    if (collisionType == PLAYER_PROJECTILE_COLLISION)
    {
        GameOver();
    }
}

void Game::GameOver()
{
    std::cout << "Game Over!" << std::endl;
    isRunning = false;
}

void Game::NextLevel()
{
}
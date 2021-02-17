#ifndef CONSTANTS_H
#define CONSTANTS_H

const unsigned int WINDOW_WIDTH = 800;  //Ширина окна
const unsigned int WINDOW_HEIGHT = 600; //Высота окна

const unsigned int FPS = 60;                       //целевое кол-во кадров
const unsigned int FRAME_TARGET_TIME = 1000 / FPS; //за сколько милисекунд должен быть отрисован один кадр

//типы коллизий
enum CollisionType 
{
    NO_COLLISION,
    PLAYER_ENEMY_COLLISION,
    PLAYER_PROJECTILE_COLLISION,
    ENEMY_PROJECTILE_COLLISION,
    PLAYER_VEGETATION_COLLISION,
    PLAYER_LEVEL_COMPLETE_COLLISION
};

//виды слоев
enum LayerType 
{
    TILE_LAYER = 0,
    VEGETATION_LAYER = 1,
    ENEMY_LAYER = 2,
    PLYAER_LAYER = 3,
    PROJECTILE_LAYER = 4,
    UI_LAYER = 5
};

const unsigned int NUM_LAYERS = 6; //количествово слоев

#endif
#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include <SDL2/SDL.h>
#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../../lib/glm/glm.hpp"
class TileComponent : public Component
{
public:
    SDL_Texture *texture;           //Текстура тайла
    SDL_Rect sourceRectangle;       //Источник
    SDL_Rect destinationRectangle;  //Местоположение
    glm::vec2 posititon;            //Положение

    TileComponent(int sourceRectX, int sourceRectY, int x, int y, int tileSize, int tileScale, std::string assetTextureId);

    ~TileComponent();
    void Initialize() override {};
    void Update(float deltaTime) override;

    void Render() override;
};

#endif
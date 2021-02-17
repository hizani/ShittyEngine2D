#include "TileComponent.h"

TileComponent::TileComponent(int sourceRectX, int sourceRectY, int x, int y, int tileSize, int tileScale, std::string assetTextureId)
{
    texture = Game::assetManager->GetTexture(assetTextureId);
    sourceRectangle.x = sourceRectX;
    sourceRectangle.y = sourceRectY;
    sourceRectangle.w = tileSize;
    sourceRectangle.h = tileSize;

    destinationRectangle.x = x;
    destinationRectangle.y = y;
    destinationRectangle.w = tileSize * tileScale;
    destinationRectangle.h = tileSize * tileScale;

    posititon.x = x;
    posititon.y = y;
}

TileComponent::~TileComponent()
{
    SDL_DestroyTexture(texture);
}

void TileComponent::Update(float deltaTime)
{
    destinationRectangle.x = posititon.x - Game::camera.x;
    destinationRectangle.y = posititon.y - Game::camera.y;
}

void TileComponent::Render()
{
    TextureManager::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
}
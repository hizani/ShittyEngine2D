#include "./TextureManager.h"
#include <iostream>

SDL_Texture *TextureManager::LoadTexture(const char *fileName)
{
    //Преобразование картинки в SDL_Surface
    SDL_Surface *surface = IMG_Load(fileName);

    std::cout << IMG_GetError() << std::endl;
    //Преобразование SDL_Surface от SDL_Texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::Draw(
    SDL_Texture *texture,
    SDL_Rect sourceRectangle,
    SDL_Rect destinationRectangle,
    SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer, texture, &sourceRectangle, &destinationRectangle, 0.0, NULL, flip);
}
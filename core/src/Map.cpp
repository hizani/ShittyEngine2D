#include <fstream>
#include "./Game.h"
#include "./Map.h"
#include "./EntityManager.h"
#include "./components/TileComponent.h"

extern EntityManager manager;

Map::Map(std::string textureId, float scale, int tileSize)
{
    this->textureId = textureId;
    this->scale = scale;
    this->tileSize = tileSize;
}

void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY)
{
    //Открытие потока
    std::fstream mapFile;
    mapFile.open(filePath);
    //Посимвольное считывание конфигурации карты
    for (int y = 0; y < mapSizeY; y++){
        for (int x = 0; x < mapSizeX; x++)
        {
            char ch;
            mapFile.get(ch);
            int sourceRectY = atoi(&ch) * tileSize;
            mapFile.get(ch);
            int sourceRectX = atoi(&ch) * tileSize;
            AddTile(sourceRectX, sourceRectY, x * (scale * tileSize), y * (scale * tileSize));
            mapFile.ignore();
        }
        //mapFile.ignore();
    }
    //Закрытие потока
    mapFile.close();
}

void Map::AddTile(int sourceRectX, int sourceRectY, int x, int y)
{
    Entity &newTile(manager.AddEntity("Tile", TILE_LAYER));
    newTile.AddComponent<TileComponent>(sourceRectX, sourceRectY, x, y, tileSize, scale, textureId);
}
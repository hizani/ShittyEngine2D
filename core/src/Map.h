#ifndef MAP_H
#define MAP_H

#include <string>

class Map
{
private:
    std::string textureId;  //Идентификатор текстуры тайлов 
    float scale;            //Степень увеличения 
    int tileSize;           //Размер тайла

public:
    Map(std::string textureId, float scale, int tileSize);
    ~Map();
    //Загрузка карты из файла
    void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
    //Создание нового тайла
    void AddTile(int sourceX, int sourceY, int x, int y);
};

#endif
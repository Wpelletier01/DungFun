#include "world/TileMap.h"

TileMap::TileMap(std::vector<std::string> textures, std::vector<int> texIndices, int tileSize, int width, int height)
{
    this->textures = textures;
    this->texIndices = texIndices;
    this->tileSize = tileSize;
    this->width = width;
    this->height = height;
}

TileMap::TileMap()
{
    tileSize = 0;
    width = 0;
    height = 0;
}

Tile TileMap::getTileAt(int x, int y)
{
    int indice = texIndices[y * width + x];
    return {x,y,this->tileSize,this->textures[indice]};
}

int TileMap::getWidth()
{
    return this->width;
}

int TileMap::getHeight()
{
    return this->height;
}

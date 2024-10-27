#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <string>
#include "Tile.h"

class TileMap
{
public:
    TileMap(std::vector<std::string> textures, std::vector<int> texIndices, int tileSize, int width, int height);
    TileMap();
    Tile getTileAt(int x, int y);
    int getWidth();
    int getHeight();

private:
    std::vector<std::string> textures;
    std::vector<int> texIndices;
    int tileSize;
    int width;
    int height;

};


#endif //TILEMAP_H

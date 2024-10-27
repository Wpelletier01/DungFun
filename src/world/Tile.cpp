#include "world/Tile.h"


Tile::Tile(int x, int y, int size, std::string texture)
{
    this->rect = SDL_Rect { x*size, y*size, size, size };
    this->texture = texture;
}


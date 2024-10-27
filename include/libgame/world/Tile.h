#ifndef TILE_H
#define TILE_H

#include <SDL_rect.h>
#include <string>


class Tile
{

public:
    Tile(int x, int y, int size, std::string texture);

    SDL_Rect rect;
    std::string texture;
};



#endif //TILE_H

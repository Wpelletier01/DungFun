#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include <filesystem>
#include <SDL_rect.h>

namespace fs = std::filesystem;

class World {
public:
    World(std::string level);
    SDL_Rect* getRect();
    std::vector<std::string>& getTilesSrc();
    std::vector<int>& getTilesMap();
    int getMapWidth();
    int getMapHeight();

private:
    int w,h;
    std::vector<std::string> tiles;
    std::vector<int> tileMap;
    SDL_Rect levelRect;
};



#endif //WORLD_H

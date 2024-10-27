#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

struct Rect
{
    SDL_Rect r;
};

struct Texture
{
    // name of the texture
    std::string id;
    // position on the source image
    SDL_Rect src;
};

struct Speed
{
    float s;
};

struct Solidity
{
    bool solid;
};



#endif //COMPONENT_H

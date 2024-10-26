#ifndef RENDERER_H
#define RENDERER_H

#include <SDL_render.h>
#include <SDL_video.h>
#include "entt.hpp"
#include "World.h"


class Renderer {
public:
    ~Renderer();
    int init(SDL_Window* win);
    void clear();
    void renderAll(entt::registry& registry, std::unordered_map<std::string, SDL_Texture*>& textures, World* world);
    void present();
    void setViewport(int x, int y);
    SDL_Renderer* getpSDLRenderer();
private:
    SDL_Renderer* mrenderer = nullptr;
};



#endif //RENDERER_H

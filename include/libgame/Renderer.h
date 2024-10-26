#ifndef RENDERER_H
#define RENDERER_H

#include <SDL_render.h>
#include <SDL_video.h>
#include "entt.hpp"
#include "World.h"

using TexRegister = std::unordered_map<std::string, SDL_Texture*>&;

class Renderer {
public:
    ~Renderer();
    int init(SDL_Window* win, entt::registry* registry);
    void clear() const;
    void renderAll(TexRegister& textures, World* world, SDL_Rect& camera);
    void present() const;
    void setViewport(int x, int y);
    SDL_Renderer* getpSDLRenderer() const;
private:
    SDL_Renderer* m_renderer = nullptr;
    entt::registry* m_registry = nullptr;
};



#endif //RENDERER_H

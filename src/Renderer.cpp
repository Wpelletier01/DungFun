#include "Renderer.h"

#include <Component.h>
#include <SDL_log.h>
#include "Declaration.h"

Renderer::~Renderer()
{
    SDL_DestroyRenderer(this->mrenderer);
}

int Renderer::init(SDL_Window *win)
{
    this->mrenderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    if (this->mrenderer == nullptr) {
        return 1;
    }

    // Set background white
    SDL_SetRenderDrawColor(this->mrenderer,255,255,255,255);


    return 0;
}

void Renderer::clear()
{
    SDL_RenderClear(this->mrenderer);
}

void Renderer::renderAll(entt::registry &registry, std::unordered_map<std::string, SDL_Texture*>& textures, World* world)
{
    // render world (level)

    SDL_Rect* worldBoundaries = world->getRect();
    SDL_Rect tileScrDest = SDL_Rect{0,0,TILE_SIZE,TILE_SIZE};

    auto tiles = world->getTilesSrc();
    auto tileMap = world->getTilesMap();
    for(int y = 0; y < worldBoundaries->h; y++) {
        tileScrDest.y = y * TILE_SIZE;
        for (int x = 0; x < worldBoundaries->w; x++) {
            SDL_RenderCopy(
                this->mrenderer,
                textures[tiles[tileMap[y*(worldBoundaries->w)+x]]],
                nullptr,
                &tileScrDest
            );

            tileScrDest.x = x*TILE_SIZE;
        }


    }

    // render entity

    auto view = registry.view<Texture,Rect>();
    for (auto entity : view) {

        auto texture = view.get<Texture>(entity);
        auto rect = view.get<Rect>(entity);


        SDL_RenderCopy(
            this->mrenderer,
            textures[texture.id],
            &texture.src,
            &rect.r
            );
    }


}

void Renderer::present()
{
    SDL_RenderPresent(this->mrenderer);
}

SDL_Renderer * Renderer::getpSDLRenderer()
{
    return this->mrenderer;
}

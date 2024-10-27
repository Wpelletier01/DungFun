#include "Renderer.h"

#include <Component.h>
#include <SDL_log.h>
#include "Declaration.h"

Renderer::~Renderer()
{
    SDL_DestroyRenderer(this->m_renderer);
}

int Renderer::init(SDL_Window *win, entt::registry* registry)
{
    this->m_renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    if (this->m_renderer == nullptr) {
        return 1;
    }

    // Set background white
    SDL_SetRenderDrawColor(this->m_renderer,255,255,255,255);

    this->m_registry = registry;

    return 0;
}

void Renderer::clear() const
{
    SDL_RenderClear(this->m_renderer);
}

void Renderer::renderAll(TexRegister textures, TileMap& tileMap, SDL_Rect& camera)
{

    SDL_Rect scrnDest = SDL_Rect{0,0,TILE_SIZE,TILE_SIZE};

    // render world (level)

    for(int y = 0; y < tileMap.getWidth(); y++) {
        for (int x = 0; x < tileMap.getHeight(); x++) {
            auto tile = tileMap.getTileAt(x,y);

            scrnDest.x = tile.rect.x - camera.x;
            scrnDest.y = tile.rect.y - camera.y;

            SDL_RenderCopy(
                this->m_renderer,
                textures[tile.texture],
                nullptr,
                &scrnDest
            );
        }
    }

    // render entities

    // same for all entity for now
    scrnDest.w = PLAYER_SPRITE_SIZE;
    scrnDest.h = PLAYER_SPRITE_SIZE;

    auto view = this->m_registry->view<Texture,Rect>();
    for (auto entity : view) {

        auto texture = view.get<Texture>(entity);
        auto rect = view.get<Rect>(entity);

        scrnDest.x = rect.r.x - camera.x;
        scrnDest.y = rect.r.y - camera.y;

        SDL_RenderCopy(
            this->m_renderer,
            textures[texture.id],
            &texture.src,
            &scrnDest
            );
    }


}

void Renderer::present() const
{
    SDL_RenderPresent(this->m_renderer);
}

SDL_Renderer * Renderer::getpSDLRenderer() const
{
    return this->m_renderer;
}

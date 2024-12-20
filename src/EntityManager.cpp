
#include "EntityManager.h"
#include "SDL2/SDL.h"
#include "Component.h"
#include "Declaration.h"

entt::entity EntityManager::createPlayer(entt::registry &registry)
{
    Rect worldRepr = Rect{SDL_Rect{ 384,256,TILE_SIZE,TILE_SIZE }};
    Texture texture = Texture{
        "player",
        SDL_Rect{0,0,PLAYER_SPRITE_SIZE,PLAYER_SPRITE_SIZE}
    };

    entt::entity id = registry.create();

    registry.emplace<Rect>(id, worldRepr);
    registry.emplace<Texture>(id, texture);
    registry.emplace<Speed>(id, Speed{5.0});
    registry.emplace<Solidity>(id,  Solidity{true});

    return id;
}

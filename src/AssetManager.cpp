#include "AssetManager.h"
#include <SDL2/SDL_image.h>

int AssetManager::init(const fs::path &imgAssetDir, SDL_Renderer *renderer)
{

    // init sdl_image
    int imgFlag = IMG_INIT_JPG | IMG_INIT_PNG;

    if (IMG_Init(imgFlag) == 0) {
        return 1;
    }

    // load image
    fs::path p;
    std::string fname;

    for (const auto &entry : fs::directory_iterator(imgAssetDir)) {

        p = entry.path();
        fname = p.stem();

        SDL_Surface *surfaceLoad = IMG_Load(p.c_str());

        if (surfaceLoad == nullptr) {
            return 1;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surfaceLoad);

        if (texture == nullptr) {
            return 1;
        }

        this->textures.insert({fname,texture});

        SDL_Log("load texture: '%s'",fname.c_str());

    }

    return 0;
}

AssetManager::~AssetManager()
{
    for (const auto& texture : this->textures ){
        SDL_DestroyTexture(texture.second);
    }
}

std::unordered_map<std::string, SDL_Texture *>& AssetManager::getTextures()
{
    return this->textures;
}

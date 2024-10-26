//
// Created by will on 23/10/24.
//

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SDL_render.h>
#include <unordered_map>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class AssetManager {

public:
    int init(const fs::path &imgAssetDir, SDL_Renderer* renderer);

    ~AssetManager();
    std::unordered_map<std::string, SDL_Texture*>& getTextures();

private:

    std::unordered_map<std::string, SDL_Texture*> textures;

};



#endif //ASSETMANAGER_H

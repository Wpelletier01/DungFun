#include "World.h"
#include <fstream>
#include <SDL_log.h>
#include <nlohmann/json.hpp>

World::World(std::string level)
{
    fs::path config = fs::path("../assets/levels/" + level);

    // For index 0 (which mean no tiles)
    this->tiles.push_back("null-128");

    std::ifstream input(config);

    if (!input.is_open()) {
        SDL_LogError(0, "couldn't open tilemap '%s'",config.c_str());
    }

    nlohmann::json data;

    try {
        input >> data;
    } catch (const nlohmann::json::parse_error& e) {
        SDL_LogError(0,"Couldn't parse json: %s", e.what());
        return;
    }


    this->w = data["width"];
    this->h = data["height"];

    this->levelRect = SDL_Rect{
        0,0,
        this->w,
        this->h
    };

    auto tilesets = data["tilesets"];

    if (!tilesets.is_array()) {
        SDL_LogError(0, "element 'tilesets' should be of type array");
        return;
    }

    for (const auto& t : tilesets) {
        this->tiles.push_back(t["name"]);
    }

    // load layer (only one for now)

    auto layers = data["layers"];

    if (!layers.is_array()) {
        SDL_LogError(0, "element 'layers' should be of type array");
        return;
    }

    for (const auto& l: layers) {
        for (const auto& i : l["data"]) {
            this->tileMap.push_back(i);
        }
    }


    input.close();
}

SDL_Rect * World::getRect()
{
    return &this->levelRect;
}

std::vector<std::string>& World::getTilesSrc()
{
    return this->tiles;
}

std::vector<int>& World::getTilesMap()
{
    return this->tileMap;
}

int World::getMapWidth()
{
    return this->w;
}

int World::getMapHeight()
{
    return this->h;
}

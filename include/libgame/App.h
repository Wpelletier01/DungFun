#ifndef APP_H
#define APP_H
#include <filesystem>
#include <SDL_events.h>
#include <SDL_video.h>
#include "Renderer.h"
#include "AssetManager.h"
#include "Camera.h"

namespace fs = std::filesystem;

const fs::path ASSET_IMG_DIR = "../assets/images";

class App {
public:
    ~App();
    int init(int screenW, int screenH, const char* title);
    void run();
private:
    void handleEvents(SDL_Event* event);
    void update(entt::entity player);
    void render();

    void handlePlayerMove(entt::entity player);

    bool running = false;
    SDL_Window* window = nullptr;
    Renderer renderer;
    AssetManager assetManager;
    entt::registry registry;
    World world = World("test-1.json");
    Camera camera;
    int screen_w, screen_h;
};



#endif //APP_H

#include "App.h"

#include <Component.h>
#include <EntityManager.h>
#include <fstream>
#include <json.hpp>
#include <SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "Declaration.h"


App::~App()
{
}

int App::init(int screenW, int screenH, const char *title)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL. '%s'\n", SDL_GetError());
        return 1;
    }

    this->window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screenW,
        screenH,
        SDL_WINDOW_SHOWN
        );

    if (this->window == nullptr) {
        SDL_LogError(0,"Couldn't create window. '%s'\n", SDL_GetError());
        return 1;
    }


    if (this->renderer.init(this->window,&this->registry) > 0) {
        SDL_LogError(0,"Couldn't initialize the renderer: '%s'",SDL_GetError());
        return 1;
    }

    if (this->assetManager.init(ASSET_IMG_DIR,this->renderer.getpSDLRenderer())) {
        SDL_LogError(0, "Couldn't initialize the Asset Manager. '%s'", SDL_GetError());
        return 1;
    }

    this->screen_h = screenH;
    this->screen_w = screenW;

    this->camera.setSize(screenW,screenH);

    return 0;

}

void App::loadLevel(std::string name)
{
    std::vector<std::string> textures;
    std::vector<int> texIndice;

    fs::path config = fs::path("../assets/levels/" + name);

    // For index 0 (which mean no tiles)
    textures.push_back("null-128");

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

    // collect width and height
    int w = data["width"];
    int h = data["height"];

    auto tilesets = data["tilesets"];

    if (!tilesets.is_array()) {
        SDL_LogError(0, "element 'tilesets' should be of type array");
        return;
    }

    for (const auto& t : tilesets) {
        textures.push_back(t["name"]);
    }

    // load layer (only one for now)

    auto layers = data["layers"];

    if (!layers.is_array()) {
        SDL_LogError(0, "element 'layers' should be of type array");
        return;
    }

    for (const auto& l: layers) {
        for (const auto& i : l["data"]) {
            texIndice.push_back(i);
        }
    }

    input.close();

    this->tileMap = TileMap(textures,texIndice,TILE_SIZE,w,h);

}

void App::run()
{

    this->loadLevel("test-1.json");

    SDL_Event event;
    this->running = true;

    auto player = EntityManager::createPlayer(this->registry);

    // for limiting frame rate to 60fps
    constexpr int fps = 60;
    constexpr int frameDelay = 1000 / fps;

    while (this->running) {

        Uint32 frameStart = SDL_GetTicks();

        this->handleEvents(&event);
        this->update(player);
        this->render();

        if (const int frameTime = SDL_GetTicks() - frameStart; frameDelay > frameTime) {
            SDL_Delay(frameDelay-frameTime);
        }
    }


}

void App::handleEvents(SDL_Event *event)
{
    while( SDL_PollEvent( event ) ) {
        switch (event->type) {
            case SDL_QUIT:
                this->running = false;
                break;
            default:
                break;
        }
    }

}

void App::update(entt::entity player)
{
    // update player position
    handlePlayerMove(player);
    // update camera
    auto&[r] = this->registry.get<Rect>(player);
    this->camera.updatePosition(r);


}

void App::render()
{
    this->renderer.clear();
    this->renderer.renderAll(
        this->assetManager.getTextures(),
        this->tileMap,
        this->camera.getRect()
        );
    this->renderer.present();
}

void App::handlePlayerMove(entt::entity player)
{
    auto& rect = this->registry.get<Rect>(player);
    auto& speed = this->registry.get<Speed>(player).s;


    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    if (keyboardState[SDL_SCANCODE_A]) {
        rect.r.x -= speed;
    }

    if (keyboardState[SDL_SCANCODE_W]) {
        rect.r.y -= speed;
    }

    if (keyboardState[SDL_SCANCODE_D]) {
        rect.r.x += speed;
    }

    if (keyboardState[SDL_SCANCODE_S]) {
        rect.r.y += speed;
    }

}

#include "App.h"

#include <Component.h>
#include <EntityManager.h>
#include <SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>


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


    if (this->renderer.init(this->window) > 0) {
        SDL_LogError(0,"Couldn't initialize the renderer: '%s'",SDL_GetError());
        return 1;
    }

    if (this->assetManager.init(ASSET_IMG_DIR,this->renderer.getpSDLRenderer())) {
        SDL_LogError(0, "Couldn't initialize the Asset Manager. '%s'", SDL_GetError());
        return 1;
    }

    this->screen_h = screenH;
    this->screen_w = screenW;

    return 0;

}

void App::run()
{
    SDL_Event event;
    this->running = true;

    auto player = EntityManager::createPlayer(this->registry);

    // for limiting frame rate to 60fps
    constexpr int fps = 60;
    constexpr int frameDelay = 1000 / fps;
    Uint32 frameStart;
    int frameTime;

    while (this->running) {

        frameStart = SDL_GetTicks();

        this->handleEvents(&event);
        this->update(player);
        this->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
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
    handlePlayerMove(player);


}

void App::render()
{
    this->renderer.clear();
    this->renderer.renderAll(this->registry,this->assetManager.getTextures(),&this->world);
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

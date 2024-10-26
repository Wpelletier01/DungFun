#include <iostream>
#include <SDL2/SDL.h>
#include "libgame/App.h"

const int WIN_WIDTH = 1600;
const int WIN_HEIGHT = 900;

int main() {

    App app;

    if (app.init(WIN_WIDTH,WIN_HEIGHT,"SDL_FUN") < 0) {
        printf("App initialisation failed");
        return 1;
    }

    app.run();

    return 0;
}

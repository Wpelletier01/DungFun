//
// Created by will on 26/10/24.
//

#ifndef CAMERA_H
#define CAMERA_H
#include <SDL_rect.h>


class Camera {
public:
    void setSize(int w, int h);
    void updatePosition(const SDL_Rect& playerRect);
    SDL_Rect& getRect();
private:
    SDL_Rect rect;
};



#endif //CAMERA_H

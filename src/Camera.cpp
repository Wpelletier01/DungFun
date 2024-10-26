//
// Created by will on 26/10/24.
//

#include "Camera.h"

void Camera::setSize(int w, int h)
{
    this->rect.w = w;
    this->rect.h = h;
}

void Camera::updatePosition(const SDL_Rect& playerRect)
{
    const int x = playerRect.x + (playerRect.w / 2) - (this->rect.w / 2);
    const int y = playerRect.y + (playerRect.h / 2) - (this->rect.h / 2);
    this->rect.x = x;
    this->rect.y = y;
}

SDL_Rect & Camera::getRect()
{
    return this->rect;
}

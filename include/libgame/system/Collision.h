#ifndef COLLISION_H
#define COLLISION_H

#include "System.h"
#include <SDL_rect.h>
#include "world/TileMap.h"

class Collision : public System {
public:
    void update(entt::registry *registry, TileMap *world) override;
private:
    bool detectRectCollision(SDL_Rect* r1, SDL_Rect* r2);

};



#endif //COLLISION_H

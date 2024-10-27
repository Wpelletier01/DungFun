#ifndef SYSTEM_H
#define SYSTEM_H
#include <entt.hpp>

#include "world/TileMap.h"


class System {
public:
    virtual void update(entt::registry* registry, TileMap* tileMap) = 0;
};



#endif //SYSTEM_H

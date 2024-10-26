#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "entt/entt.hpp"

class EntityManager {

public:

    // helper function to create entity

    // player
    static entt::entity createPlayer(entt::registry& registry);


};



#endif //ENTITYMANAGER_H

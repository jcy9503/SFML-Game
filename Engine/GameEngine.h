#pragma once

#include "../Entities/Entity.h"

class GameEngine
{
public:
    static void initialize();
    static void main_loop();
    static void enemy_spawner(float size, ENEMY_TYPE type);
};

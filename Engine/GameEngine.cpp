#include "GameEngine.h"

#include "../stdafx.h"
#include "../Components/Shape.h"
#include "../Systems/SInput.h"
#include "../Systems/SInterface.h"
#include "../Systems/SPhysics.h"
#include "../Systems/SRender.h"
#include "../Components/Rand.h"
#include "../Components/Transform.hpp"

void GameEngine::initialize()
{
    Rand::initialize();
    
    std::ifstream config("config.txt");
    std::string   s;
    while (config >> s)
    {
        if (s == "Window")
        {
            sf::Vector2u size;
            std::string  title;
            config >> size.x >> size.y >> title;
            window.create(sf::VideoMode(size.x, size.y), window_title);
            window.setFramerateLimit(60);
            window_size = size;
        }
        else if (s == "Font")
        {
            std::string filepath;
            int         size;
            sf::Color   color;
            config >> filepath >> size >> color;
        }
    }

    ImGui::SFML::Init(window);

    EntityManager::get().reset();
    const auto player = EntityManager::get().add_entity("Player", window_size / 2.f,
                                                        vec2_zero, RADIUS_PLAYER, 0);
    player->shape->circle.setPointCount(20);
    player->shape->circle.setFillColor(sf::Color::White);
    player->shape->circle.setOutlineColor(sf::Color::Red);
    player->shape->circle.setOutlineThickness(1.f);
	player->transform->velocity = vec2_zero;
	player->transform->speed = 1.f;
}

void GameEngine::main_loop()
{
    EntityManager::get().update();
    SInput::get().update();
    SInterface::get().update();
    SPhysics::get().update();
    SRender::get().update();
}

void GameEngine::enemy_spawner(const float size, const ENEMY_TYPE type)
{
    auto e = EntityManager::get().add_entity("Enemy",
                                             Rand::random_pos(size),
                                             Rand::random_vel(), size, type);
}

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
			window_size = size;
		}
		else if (s == "Font")
		{
			std::string filepath;
			int         size;
			sf::Color   color;
			config >> filepath >> size >> color;
			SInterface::get().initialize(filepath);
		}
	}

	SPhysics::get().initialize();
	reset();
}

void GameEngine::reset()
{
	EntityManager::get().reset();
	const auto player =
			EntityManager::get().add_entity("Player", window_size / 2.f,
			                                vec2_zero, PLAYER_RADIUS, 0,
			                                PLAYER_SEG_COUNT, sf::Color::White);
	player->shape->circle.setOutlineColor(sf::Color::Red);
	player->shape->circle.setOutlineThickness(1.f);
	player->transform->friction = 5.f;
	resume();
	SInterface::get().game_over(false);
}

void GameEngine::main_loop()
{
	m_clock.restart();
	EntityManager::get().update();
	SInput::get().update();
	SPhysics::get().update();
	SInterface::get().update();
	SRender::get().update();

	delta_time = m_clock.getElapsedTime().asSeconds();
	if (paused) return;

	m_elapsed += delta_time;
	if (m_elapsed > m_enemyInterval)
	{
		enemy_spawner(Rand::random(enemy_radius.x, enemy_radius.y), ENEMY_NORMAL);
		m_elapsed -= m_enemyInterval;
	}
}

void GameEngine::enemy_spawner(const float size, const ENEMY_TYPE type)
{
	const auto e = EntityManager::get().add_entity
			("Enemy",
			 Rand::random_pos(size),
			 Rand::random_vel(), size, type,
			 Rand::random_segments(), Rand::random_color());
	e->shape->rotation_speed = e->transform->speed;
}

void GameEngine::pause()
{
	paused                  = true;
	SInput::get().enabled   = false;
	SPhysics::get().enabled = false;
	SInterface::get().pause(true);
}

void GameEngine::resume()
{
	paused                  = false;
	SInput::get().enabled   = true;
	SPhysics::get().enabled = true;
	SInterface::get().pause(false);
}

bool GameEngine::game_over_predicate()
{
	return EntityManager::get().get_player()->info->player_info->health <= 0;
}

void GameEngine::game_over()
{
	if (game_over_predicate())
	{
		paused                  = true;
		SInput::get().enabled   = false;
		SPhysics::get().enabled = false;
		SInterface::get().game_over(true);
	}
}
#pragma once

#include "../Entities/Entity.h"

class GameEngine
{
	GameEngine()  = default;
	~GameEngine() = default;

	sf::Clock m_clock         = {};
	float     m_enemyInterval = 1.f;
	float     m_elapsed       = 0.f;

public:
	static GameEngine& get()
	{
		static GameEngine gameEngine;
		return gameEngine;
	}

	GameEngine(GameEngine const&)            = delete;
	GameEngine(GameEngine&&)                 = delete;
	GameEngine& operator=(GameEngine const&) = delete;
	GameEngine& operator=(GameEngine&&)      = delete;

	void initialize();
	void main_loop();
	void enemy_spawner(float size, ENEMY_TYPE type);
};
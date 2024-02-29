#pragma once

#include "Entity.h"
#include "../Math.hpp"
#include "../Components/BBox.h"
#include "../Components/Shape.h"
#include "../Components/Transform.hpp"
#include "../Engine/GameEngine.h"

/* Entity behavior methods
 * -----------------------
 * - Contains interactions between entities
 */

static void fire()
{
	const auto playerInfo = EntityManager::get().get_player()->info->player_info;

	const auto spawned = entity_circle_spawner
			("Bullet",
			 EntityManager::get().get_player()->bbox->get_center(),
			 playerInfo->fire_dir,
			 playerInfo->bullet_speed,
			 playerInfo->bullet_radius,
			 BULLET_NORMAL, BULLET_SEG_COUNT, sf::Color::Red);

	for (const auto& entity : spawned)
	{
		entity->shape->point_count = 10;
	}
}

static void gain_points(const std::shared_ptr<Entity>& bullet, const std::shared_ptr<Entity>& enemy)
{
	EntityManager::get().get_player()->info->player_info->score +=
			power_int(10, static_cast<int>(enemy->info->enemy_type) + 1) *
			static_cast<int>(enemy->shape->get_point_count());

	bullet->destroy();
	switch (enemy->info->enemy_type)
	{
	case ENEMY_NORMAL: entity_circle_spawner
				("Enemy",
				 enemy->bbox->get_center(),
				 enemy->shape->point_count,
				 enemy->transform->speed,
				 enemy->shape->radius / 2,
				 ENEMY_FRAG, enemy->shape->point_count,
				 enemy->shape->color);
		[[fallthrough]];
	case ENEMY_FRAG: enemy->destroy();
	}
}

static void lose_health(const std::shared_ptr<Entity>& player, const std::shared_ptr<Entity>& enemy)
{
	if (player->info->player_info == nullptr) error("Accessing player_info of non-player entity", 4);

	player->info->player_info->health -= 10;
	enemy->destroy();

	GameEngine::get().game_over();
}
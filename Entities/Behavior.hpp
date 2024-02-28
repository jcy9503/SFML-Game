#pragma once

#include "Entity.h"
#include "../Components/BBox.h"
#include "../Components/Shape.h"
#include "../Components/Transform.hpp"

/* Entity behavior methods
 * -----------------------
 * - Contains player-related procedures.
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
			10 * static_cast<int>(enemy->info->enemy_type) * static_cast<int>(enemy->shape->get_point_count());

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
#pragma once

#include "Entity.h"
#include "../Components/BBox.h"
#include "../Components/Shape.h"

/* Entity behavior methods
 * -----------------------
 * - Contains player-related procedures.
 */

static void fire()
{
    const auto player  = EntityManager::get().get_player();
    const Vec2 firePos = player->bbox->get_center();

    player->info->player_info->fire_dir_calculation();
    for (auto dir : player->info->player_info->fire_dir)
    {
        EntityManager::get().add_entity("Bullet", firePos,
                                        dir * player->info->player_info->bullet_speed,
                                        RADIUS_BULLET, 0);
    }
}

static void gain_points(const std::shared_ptr<Entity>& bullet, const std::shared_ptr<Entity>& enemy)
{
    EntityManager::get().get_player()->info->player_info->score +=
        10 * static_cast<int>(enemy->info->enemy_type) * static_cast<int>(enemy->shape->get_point_count());

    bullet->destroy();
    enemy->destroy();
}

#include "../stdafx.h"
#include "Entity.h"

#include "../Components/BBox.h"
#include "../Components/Shape.h"
#include "../Components/Transform.hpp"
#include "../Components/Math.hpp"

/* PlayerInfo structure
 * --------------------
 * - Contains property method for inner member variables.
 */

void PlayerInfo::fire_dir_calculation()
{
	if (fire_dir_tp == fire_dir_count) return;
	fire_dir_tp = fire_dir_count;

	const auto& player = EntityManager::get().get_player();

	if (player == nullptr ||
	    player->info->player_info->fire_dir.size() == static_cast<size_t>(fire_dir_count))
		return;

	player->info->player_info->fire_dir.clear();
	for (size_t i = 0; i < fire_dir_count; ++i)
	{
		player->info->player_info->fire_dir.push_back({
			                                              cosf(static_cast<float>(i) * (
				                                                   Math::pi_f / static_cast<float>(fire_dir_count) /
				                                                   2)),
			                                              sinf(static_cast<float>(i) * (
				                                                   Math::pi_f / static_cast<float>(fire_dir_count) / 2))
		                                              });
	}
}

Entity::Entity(const size_t id)
	: m_id(id) {}

Entity::Entity(std::string tag, const size_t id)
	: m_id(id), m_tag(std::move(tag)) {}

void Entity::reuse(const std::string& tag)
{
	m_tag  = tag;
	m_dead = false;
}

/* Entity Manager
 * --------------
 * - Contains all methods controlling entity lists.
 * 
 */
void EntityManager::update()
{
	for (const auto& e : m_toAdd)
	{
		m_entities.insert(e);
		m_entityMap[e->tag()].insert(e);
	}
	m_toAdd.clear();

	for (auto eIter = m_entities.begin(); eIter != m_entities.end(); ++eIter)
	{
		if ((*eIter)->dead())
		{
			(*eIter)->info->player_info = nullptr;
			m_deleted.push_back(*eIter);

			std::string tag = (*eIter)->tag();
			for (auto eTagIter = m_entityMap[tag].begin();
			     eTagIter != m_entityMap[tag].end(); ++eTagIter)
			{
				if (*eTagIter == *eIter)
				{
					m_entityMap[tag].erase(eTagIter);
				}
			}
			m_entities.erase(eIter);
		}
	}
}

void EntityManager::reset()
{
	m_entities.clear();
	m_toAdd.clear();
	m_deleted.clear();
	for (auto entities : m_entityMap)
	{
		entities.second.clear();
	}
	m_entityMap.clear();
	m_totalEntities = 0;
}

std::shared_ptr<Entity> EntityManager::add_entity(
	const std::string& tag, const Vec2& pos,
	const Vec2&        vel, const float size, const int type)
{
	std::shared_ptr<Entity> entity;

	if (m_deleted.empty())
	{
		entity            = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities));
		entity->transform = std::make_shared<Transform>(vel);
		entity->shape     = std::make_shared<Shape>(pos, size);
		entity->bbox      = std::make_shared<BBox>(pos, size);
		entity->info      = std::make_shared<EntityInfo>();
		m_toAdd.insert(entity);
	}
	else
	{
		entity = m_deleted.back();
		entity->reuse(tag);
		entity->transform->set_velocity(vel);
		entity->shape->reset_position(pos);
		entity->bbox->reset(pos, size);
		m_toAdd.insert(entity);
		m_deleted.pop_back();
	}

	if (tag == "Enemy")
	{
		entity->info->enemy_type = static_cast<ENEMY_TYPE>(type);
	}
	else if (tag == "Player")
	{
		entity->info->player_type                 = static_cast<PLAYER_TYPE>(type);
		entity->info->player_info                 = std::make_shared<PlayerInfo>();
		m_player                                  = entity;
		entity->info->player_info->fire_dir_count = 10;
	}

	++m_totalEntities;

	return entity;
}

ENTITY_SET& EntityManager::get_entities()
{
	return m_entities;
}

ENTITY_SET& EntityManager::get_entities(const std::string& tag)
{
	return m_entityMap[tag];
}

std::shared_ptr<Entity> EntityManager::get_player()
{
	return m_player;
}
#include "../stdafx.h"
#include "Entity.h"

#include "../Components/BBox.h"
#include "../Components/Shape.h"
#include "../Components/Transform.hpp"
#include "../Math.hpp"

Entity::Entity(const size_t id)
	: m_id(id) {}

Entity::Entity(std::string tag, const size_t id)
	: m_id(id), m_tag(std::move(tag)) {}

void Entity::reuse(const std::string& tag)
{
	m_tag  = tag;
	m_dead = false;
}

std::vector<std::shared_ptr<Entity>> entity_circle_spawner(
	const std::string& tag, const Vec2&           pos, const size_t direction,
	const float        speed, const float         size, const int   type,
	const size_t       segments, const sf::Color& col)
{
	const std::vector<Vec2>              dirs = Math::circle_dir_calc(direction);
	std::vector<std::shared_ptr<Entity>> spawned(direction);

	for (size_t i = 0; i < dirs.size(); ++i)
	{
		spawned[i] =
				EntityManager::get().add_entity(tag, pos,
				                                dirs[i] * speed, size,
				                                type, segments, col);
	}

	return spawned;
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

	for (auto eIter = m_entities.begin(); eIter != m_entities.end();)
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
					break;
				}
			}
			const auto iterTp = std::next(eIter);
			m_entities.erase(eIter);
			eIter = iterTp;

			continue;
		}
		++eIter;
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
	const std::string& tag, const Vec2&   pos, const Vec2&           vel, const float size,
	const int          type, const size_t segments, const sf::Color& col)
{
	std::shared_ptr<Entity> entity;

	if (m_deleted.empty())
	{
		entity            = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
		entity->transform = std::make_shared<Transform>(vel);
		entity->shape     = std::make_shared<Shape>(pos, size, segments, col, vel.length());
		entity->bbox      = std::make_shared<BBox>(pos, size);
		entity->info      = std::make_shared<EntityInfo>();
		m_toAdd.insert(entity);
	}
	else
	{
		entity = m_deleted.back();
		entity->reuse(tag);
		entity->transform->set_velocity(vel);
		entity->shape->reset(pos, segments, size, vel.length(), col);
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
		entity->info->player_type = static_cast<PLAYER_TYPE>(type);
		entity->info->player_info = std::make_shared<PlayerInfo>();
		m_player                  = entity;
	}

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
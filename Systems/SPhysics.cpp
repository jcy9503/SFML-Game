#include "../stdafx.h"
#include "SPhysics.h"

#include "../Math.hpp"
#include "../Entities/Behavior.hpp"

void SPhysics::initialize()
{
	add_event([]
	{
		circle_collision(EntityManager::get().get_entities("Bullet"),
			EntityManager::get().get_entities("Enemy"),
			gain_points);
		circle_collision(EntityManager::get().get_entities("Player"),
			EntityManager::get().get_entities("Enemy"),
			lose_health);
	});
}

void SPhysics::update() const
{
	if (!enabled) return;

	move();
	friction();
	bounce_window(EntityManager::get().get_entities("Enemy"));
	bounce_window(EntityManager::get().get_entities("Player"));
	stick_to_window();
	destroy_out_objs(EntityManager::get().get_entities("Bullet"));
	collision_event();
}

void SPhysics::move(const ENTITY_SET& entities)
{
	for (const auto& entity : entities)
	{
		entity->shape->update_position_offset(entity->transform->get_velocity());
		entity->bbox->update_position(entity->shape->get_position());
	}
}

void SPhysics::destroy_out_objs(const ENTITY_SET& entities)
{
	for (const auto& entity : entities)
	{
		if (window_out(*entity->bbox))
		{
			entity->destroy();
		}
	}
}

void SPhysics::bounce_window(const ENTITY_SET& entities)
{
	for (const auto& entity : entities)
	{
		if (window_bounce_horizontal(*entity->bbox)) entity->transform->bounce_horizontal();
		if (window_bounce_vertical(*entity->bbox)) entity->transform->bounce_vertical();
	}
}

void SPhysics::friction(const ENTITY_SET& entities)
{
	for (const auto& entity : entities)
	{
		if (entity->transform->friction < FLT_EPSILON) continue;
		entity->transform->speed = lerp(entity->transform->speed, 0.f,
		                                delta_time * entity->transform->friction);
	}
}

void SPhysics::stick_to_window(const ENTITY_SET& entities)
{
	for (const auto& entity : entities)
	{
		if (window_bounce_horizontal(*entity->bbox) || window_bounce_vertical(*entity->bbox))
		{
			const Vec2 pos          = entity->bbox->get_in_window_position();
			entity->shape->position = pos;
		}
	}
}

void SPhysics::add_event(void (*event)())
{
	m_colEvent.push_back(event);
}

void SPhysics::collision_event() const
{
	for (const auto event : m_colEvent)
	{
		event();
	}
}

void SPhysics::circle_collision(
	const ENTITY_SET& group1, const ENTITY_SET& group2,
	void (*           callback)(const std::shared_ptr<Entity>&, const std::shared_ptr<Entity>&))
{
	for (const auto& e1 : group1)
	{
		for (const auto& e2 : group2)
		{
			if (intersect_circles(*e1->bbox, *e2->bbox)) callback(e1, e2);
		}
	}
}

void SPhysics::box_collision(
	const ENTITY_SET& group1, const ENTITY_SET& group2,
	void (*           callback)(const std::shared_ptr<Entity>&, const std::shared_ptr<Entity>&))
{
	for (const auto& e1 : group1)
	{
		for (const auto& e2 : group2)
		{
			if (intersect_boxes(*e1->bbox, *e2->bbox)) callback(e1, e2);
		}
	}
}
#pragma once

#include "../Entities/Entity.h"

class SPhysics
{
	SPhysics()  = default;
	~SPhysics() = default;

	sf::Clock              m_clock    = {};
	std::vector<void(*)()> m_colEvent = {};

public:
	static SPhysics& get()
	{
		static SPhysics physicsSystem;
		return physicsSystem;
	}

	SPhysics(SPhysics const&)            = delete;
	SPhysics(SPhysics&&)                 = delete;
	SPhysics& operator=(SPhysics const&) = delete;
	SPhysics& operator=(SPhysics&&)      = delete;

	void        initialize();
	void        update() const;
	static void move(const ENTITY_SET& entities = EntityManager::get().get_entities());
	static void destroy_out_objs(const ENTITY_SET& entities = EntityManager::get().get_entities());
	static void bounce_window(const ENTITY_SET& entities = EntityManager::get().get_entities());
	static void friction(const ENTITY_SET& entities = EntityManager::get().get_entities("Player"));
	static void stick_to_window(const ENTITY_SET& entities = EntityManager::get().get_entities("Player"));
	void        add_event(void (*event)());
	void        collision_event() const;

	static void circle_collision(
		const ENTITY_SET& group1, const ENTITY_SET& group2,
		void (*           callback)(const std::shared_ptr<Entity>&, const std::shared_ptr<Entity>&));
	static void box_collision(
		const ENTITY_SET& group1, const ENTITY_SET& group2,
		void (*           callback)(const std::shared_ptr<Entity>&, const std::shared_ptr<Entity>&));

	bool enabled = true;
};
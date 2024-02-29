#pragma once
#include <set>

#include "../stdafx.h"

class Transform;
class Name;
class Shape;
class BBox;
class Entity;

enum ENEMY_TYPE
{
	ENEMY_NORMAL = 0,
	ENEMY_FRAG,
};

enum PLAYER_TYPE
{
	PLAYER_NORMAL = 0,
	PLAYER_DEBUG,
};

enum BULLET_TYPE
{
	BULLET_NORMAL = 0,
};

struct PlayerInfo
{
	float player_speed  = 500.f;
	float bullet_speed  = 100.f;
	float bullet_radius = BULLET_RADIUS;
	int   score         = 0;
	int   fire_dir      = 10;
	int   health        = 100;
};

struct EntityInfo
{
	union
	{
		ENEMY_TYPE  enemy_type;
		PLAYER_TYPE player_type;
		BULLET_TYPE bullet_type;
	};

	std::shared_ptr<PlayerInfo> player_info = nullptr;
};

class Entity
{
	size_t      m_id   = 0;
	std::string m_tag  = "Default";
	bool        m_dead = false;

protected:
	Entity() = default;
	explicit Entity(size_t id);
	explicit Entity(std::string tag, size_t id);

public:
	std::shared_ptr<Transform>  transform;
	std::shared_ptr<Shape>      shape;
	std::shared_ptr<BBox>       bbox;
	std::shared_ptr<EntityInfo> info;

	const std::string& tag() { return m_tag; }

	[[nodiscard]] bool dead() const { return m_dead; }
	void               destroy() { m_dead = true; }
	void               reuse(const std::string& tag);

	friend class EntityManager;
};

std::vector<std::shared_ptr<Entity>> entity_circle_spawner(
	const std::string& tag, const Vec2& pos, size_t direction,
	float              speed, float     size, int   type, size_t segments, const sf::Color& col);

using ENTITY_VECTOR = std::vector<std::shared_ptr<Entity>>;
using ENTITY_SET = std::set<std::shared_ptr<Entity>>;
using ENTITY_MAP = std::map<std::string, ENTITY_SET>;

class EntityManager
{
	EntityManager() {}
	~EntityManager() = default;

	ENTITY_SET              m_entities      = {};
	ENTITY_SET              m_toAdd         = {};
	ENTITY_VECTOR           m_deleted       = {};
	ENTITY_MAP              m_entityMap     = {};
	std::shared_ptr<Entity> m_player        = {};
	size_t                  m_totalEntities = 0;

public:
	static EntityManager& get()
	{
		static EntityManager entityManager;
		return entityManager;
	}

	EntityManager(EntityManager const&)            = delete;
	EntityManager(EntityManager&&)                 = delete;
	EntityManager& operator=(EntityManager const&) = delete;
	EntityManager& operator=(EntityManager&&)      = delete;

	void update();
	void reset();

	std::shared_ptr<Entity> add_entity(
		const std::string& tag, const Vec2& pos,
		const Vec2&        vel, float       size, int type, size_t segments, const sf::Color& col);
	ENTITY_SET&             get_entities();
	ENTITY_SET&             get_entities(const std::string& tag);
	[[nodiscard]] size_t    get_deleted_count() const { return m_deleted.size(); }
	std::shared_ptr<Entity> get_player();
	[[nodiscard]] size_t    get_entity_count() const { return m_totalEntities; }
};
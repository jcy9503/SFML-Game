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
    NORMAL = 1,
    FRAG,
};

enum PLAYER_TYPE
{
    DEBUG = 0,
};

struct PlayerInfo
{
    float bullet_speed = 1.f;
    int   score        = 0;

    int               fire_dir_tp    = 10;
    int               fire_dir_count = 10;
    std::vector<Vec2> fire_dir;

    void fire_dir_calculation();
};

struct EntityInfo
{
    union
    {
        ENEMY_TYPE  enemy_type;
        PLAYER_TYPE player_type;
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

    bool dead() const { return m_dead; }
    void destroy() { m_dead = true; }
    void reuse(const std::string& tag);

    friend class EntityManager;
};

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
	    const Vec2&        vel, float       size, int type);
    ENTITY_SET&             get_entities();
    ENTITY_SET&             get_entities(const std::string& tag);
    std::shared_ptr<Entity> get_player();
    size_t                  get_entity_count() const { return m_totalEntities; }
};

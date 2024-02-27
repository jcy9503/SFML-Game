#pragma once
#include "../Entities/Entity.h"

class SPhysics
{
    SPhysics()  = default;
    ~SPhysics() = default;

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

    void        update() const;
    static void move(const ENTITY_SET& entities = EntityManager::get().get_entities());
    static void bounce(const ENTITY_SET& entities = EntityManager::get().get_entities());
    static void circle_collision(
        const ENTITY_SET& group1, const ENTITY_SET& group2,
        void (*            callback)(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2));
    static void box_collision(
        const ENTITY_SET& group1, const ENTITY_SET& group2,
        void (*            callback)(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2));

    bool enabled = true;
};

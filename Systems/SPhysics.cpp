#include "../stdafx.h"
#include "SPhysics.h"
#include "../Components/Transform.hpp"
#include "../Components/BBox.h"
#include "../Components/Shape.h"

void SPhysics::update() const
{
    if (!enabled)
        return;

    move(EntityManager::get().get_entities());

    bounce(EntityManager::get().get_entities("Enemy"));
}

void SPhysics::move(const ENTITY_SET& entities)
{
    for(auto iter = entities.begin(); iter != entities.end(); ++iter)
    {
        Vec2 vel = (*iter)->transform->get_velocity();
        (*iter)->bbox->update_position_offset(vel);
        (*iter)->shape->update_position_offset(vel);
    }
}

void SPhysics::bounce(const ENTITY_SET& entities)
{
    for (const auto& entity : entities)
    {
        if (window_bounce_horizontal(*entity->bbox))
            entity->transform->bounce_horizontal();
        if (window_bounce_vertical(*entity->bbox))
            entity->transform->bounce_vertical();
    }
}

void SPhysics::circle_collision(
    const ENTITY_SET& group1, const ENTITY_SET& group2,
    void (*            callback)(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2))
{
    for (const auto& e1 : group1)
    {
        for (const auto& e2 : group2)
        {
            if (intersect_circles(*e1->bbox, *e2->bbox))
                callback(e1, e2);
        }
    }
}

void SPhysics::box_collision(
    const ENTITY_SET& group1, const ENTITY_SET& group2,
    void (*            callback)(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2))
{
    for (const auto& e1 : group1)
    {
        for (const auto& e2 : group2)
        {
            if (intersect_boxes(*e1->bbox, *e2->bbox))
                callback(e1, e2);
        }
    }
}

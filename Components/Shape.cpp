#include "../stdafx.h"
#include "Shape.h"
#include "Rand.h"

Shape::Shape(const Vec2& pos, const float radius)
    : Shape(pos, radius, Rand::random_segments(), Rand::random_color()) {}

Shape::Shape(
    const Vec2&      pos, const float radius, const int segments,
    const sf::Color& color)
    : circle(radius, segments), m_radius(radius), m_pointCount(segments), m_color(color)
{
    circle.setPosition(pos.x, pos.y);
    circle.setFillColor(color);
}

void Shape::reset_position(const Vec2& pos)
{
    circle.setPosition(pos.x, pos.y);
}

void Shape::update_position_offset(const Vec2& vel)
{
    circle.setPosition(circle.getPosition() + vel);
}

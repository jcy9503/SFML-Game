#include "../stdafx.h"
#include "Shape.h"

Shape::Shape(
	const Vec2&      pos, const float   rad, const int segments,
	const sf::Color& col, const float rot_speed)
	: m_pos(pos), m_pointCount(segments), m_color(col), m_radius(rad),
	  m_rotSpeed(rot_speed), circle(rad, segments)
{
	position = pos;
	point_count = segments;
	color = col;
	radius = rad;
	circle.setOrigin(rad, rad);
}

void Shape::reset(
	const Vec2& pos, const size_t           p_count, const float rad,
	const float rot_speed, const sf::Color& col)
{
	position       = pos;
	point_count    = p_count;
	color          = col;
	radius         = rad;
	rotation_speed = rot_speed;
	circle.setOrigin(rad, rad);
}

void Shape::update_position_offset(const Vec2& vel)
{
	if (vel == vec2_zero) return;
	position = position + vel * delta_time;
}

void Shape::update_rotation()
{
	circle.setRotation(circle.getRotation() + rotation_speed * delta_time);
}
#include "../stdafx.h"
#include "Shape.h"

Shape::Shape(
	const Vec2&      pos, const float rad, const int segments,
	const sf::Color& col, const float rot_speed)
	: m_pos(pos), m_pointCount(segments), m_color(col), m_radius(rad),
	  m_rotSpeed(rot_speed), circle(rad, segments)
{
	position    = pos;
	point_count = segments;
	color       = col;
	radius      = rad;
	circle.setOrigin(rad, rad);
}

void Shape::reset(
	Shape&      obj, const Vec2& pos, const size_t           p_count,
	const float rad, const float rot_speed, const sf::Color& col)
{
	obj.position       = pos;
	obj.point_count    = p_count;
	obj.color          = col;
	obj.radius         = rad;
	obj.rotation_speed = rot_speed;
	obj.circle.setOrigin(rad, rad);
}

void Shape::update_position_offset(Shape& obj, const Vec2& vel)
{
	if (vel == vec2_zero) return;
	obj.position = obj.position + vel * delta_time;
}

void Shape::update_rotation(Shape& obj)
{
	obj.circle.setRotation(obj.circle.getRotation() +
	                       obj.rotation_speed * delta_time);
}
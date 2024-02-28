#include "../stdafx.h"
#include "../Math.hpp"
#include "BBox.h"

void BBox::reset(const Vec2& pos, const float radius)
{
	pos_x = pos.x;
	pos_y = pos.y;
	width = height = radius;
}

Vec2 BBox::get_center() const { return Vec2{pos_x, pos_y}; }

float BBox::get_east() const { return pos_x + width / 2.f; }

float BBox::get_west() const { return pos_x - width / 2.f; }

float BBox::get_north() const { return pos_y - height / 2.f; }

float BBox::get_south() const { return pos_y + height / 2.f; }

Vec2 BBox::get_northeast() const { return Vec2{get_east(), get_north()}; }

Vec2 BBox::get_northwest() const { return Vec2{get_west(), get_north()}; }

Vec2 BBox::get_southeast() const { return Vec2{get_east(), get_south()}; }

Vec2 BBox::get_southwest() const { return Vec2{get_west(), get_south()}; }

Vec2 BBox::get_in_window_position()
{
	const auto pos = Vec2{
		clamp(pos_x, width / 2, window_size.x - width / 2),
		clamp(pos_y, height / 2, window_size.y - height / 2)
	};
	pos_x = pos.x;
	pos_y = pos.y;

	return pos;
}

void BBox::update_position(const Vec2& pos)
{
	pos_x = pos.x;
	pos_y = pos.y;
}

void BBox::update_position_offset(const Vec2& vel)
{
	if (vel == vec2_zero) return;
	pos_x += vel.x;
	pos_y += vel.y;
}

bool window_bounce_horizontal(const BBox& obj)
{
	return obj.get_east() >= window_size.x || obj.get_west() <= 0.f;
}

bool window_bounce_vertical(const BBox& obj)
{
	return obj.get_south() >= window_size.y || obj.get_north() <= 0.f;
}

bool window_out(const BBox& obj)
{
	return obj.get_west() >= window_size.x ||
	       obj.get_east() <= 0.f ||
	       obj.get_north() >= window_size.y ||
	       obj.get_south() <= 0.f;
}

bool intersect_circles(const BBox& lhs, const BBox& rhs)
{
	const float radiusSum = (lhs.width + rhs.width) / 2.f;
	return radiusSum * radiusSum >
	       lhs.get_center().dist_to_sqr(rhs.get_center());
}

bool intersect_boxes(const BBox& lhs, const BBox& rhs)
{
	return value_in_range(lhs.get_west(), rhs.get_west(), rhs.get_east()) ||
	       value_in_range(rhs.get_west(), lhs.get_west(), lhs.get_east()) &&
	       value_in_range(lhs.get_north(), rhs.get_north(), rhs.get_south()) ||
	       value_in_range(rhs.get_north(), lhs.get_north(), lhs.get_south());
}
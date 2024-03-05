#pragma once

/*        width
 *       ┌─────┐
 * height│  ┼  │ <- center {pos_x, pos_y}
 *       └─────┘
 */
class BBox
{
public:
	float pos_x;
	float pos_y;
	float width;
	float height;

	explicit BBox(const Vec2& pos, const float radius)
		: BBox(pos.x, pos.y, radius * 2.f, radius * 2.f) {}

	BBox(const float x, const float y, const float width, const float height)
		: pos_x(x), pos_y(y), width(width), height(height) {}

	static void         reset(BBox& obj, const Vec2& pos, float radius);
	[[nodiscard]] Vec2  get_center() const;
	[[nodiscard]] float get_east() const;
	[[nodiscard]] float get_west() const;
	[[nodiscard]] float get_south() const;
	[[nodiscard]] float get_north() const;

	[[nodiscard]] Vec2 get_northeast() const;
	[[nodiscard]] Vec2 get_northwest() const;
	[[nodiscard]] Vec2 get_southeast() const;
	[[nodiscard]] Vec2 get_southwest() const;

	[[nodiscard]] Vec2 get_in_window_position();
	static void        update_position(BBox& obj, const Vec2& pos);
	static void        update_position_offset(BBox& obj, const Vec2& vel);

	static bool window_bounce_horizontal(const BBox& obj);
	static bool window_bounce_vertical(const BBox& obj);
	static bool window_out(const BBox& obj);
	static bool intersect_circles(const BBox& lhs, const BBox& rhs);
	static bool intersect_boxes(const BBox& lhs, const BBox& rhs);
};
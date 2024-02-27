#pragma once

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

    void                reset(const Vec2& pos, float radius);
    [[nodiscard]] Vec2  get_center() const;
    [[nodiscard]] float get_east() const;
    [[nodiscard]] float get_north() const;
    [[nodiscard]] Vec2  get_northeast() const;
    [[nodiscard]] Vec2  get_northwest() const;
    [[nodiscard]] float get_south() const;
    [[nodiscard]] Vec2  get_southeast() const;
    [[nodiscard]] Vec2  get_southwest() const;
    [[nodiscard]] float get_west() const;
    void                update_position(const Vec2& pos);
    void                update_position_offset(const Vec2& vel);
};

bool window_bounce_east(const BBox& obj);
bool window_bounce_west(const BBox& obj);
bool window_bounce_south(const BBox& obj);
bool window_bounce_north(const BBox& obj);
bool window_bounce_horizontal(const BBox& obj);
bool window_bounce_vertical(const BBox& obj);
bool intersect_circles(const BBox& lhs, const BBox& rhs);
bool intersect_boxes(const BBox& lhs, const BBox& rhs);

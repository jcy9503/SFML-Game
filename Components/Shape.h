#pragma once

class Shape
{
    size_t    m_pointCount;
    sf::Color m_color;
    float     m_radius;

public:
    explicit Shape(const Vec2& pos, float radius);
    Shape(const Vec2& pos, float radius, int segments, const sf::Color& color);

    void reset_position(const Vec2& pos);
    void update_position_offset(const Vec2& vel);

    sf::CircleShape circle;

    /* radius property */
    [[nodiscard]] float get_radius() const { return m_radius; }

    void put_radius(const float val)
    {
        m_radius = val;
        circle.setRadius(m_radius);
    }

    __declspec(property(get = get_radius, put = put_radius))
    float radius;

    /* point count property */
    [[nodiscard]] size_t get_point_count() const { return m_pointCount; }

    void put_point_count(const size_t val)
    {
        m_pointCount = val;
        circle.setPointCount(m_pointCount);
    }

    __declspec(property(get = get_point_count, put = put_point_count))
    size_t point_count;

    /* color property */
    [[nodiscard]] sf::Color get_color() const { return m_color; }

    void put_color(const sf::Color& val)
    {
        m_color = val;
        circle.setFillColor(m_color);
    }

    __declspec(property(get = get_color, put = put_color))
    sf::Color color;
};

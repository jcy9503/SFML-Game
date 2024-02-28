#pragma once

class Shape
{
	Vec2      m_pos;
	size_t    m_pointCount;
	sf::Color m_color;
	float     m_radius;
	float     m_rotSpeed;

public:
	Shape(const Vec2& pos, float rad, int segments, const sf::Color& col, float rot_speed);

	void reset(const Vec2& pos, size_t p_count, float rad, float rot_speed, const sf::Color& col);
	void update_position_offset(const Vec2& vel);
	void update_rotation();

	sf::CircleShape circle;

	/* position property */
	[[nodiscard]] Vec2 get_position() const { return m_pos; }

	void set_position(const Vec2& val)
	{
		m_pos = val;
		circle.setPosition(val.x, val.y);
	}

	__declspec(property(get = get_position, put = set_position))
	Vec2 position;

	/* radius property */
	[[nodiscard]] float get_radius() const { return m_radius; }

	void set_radius(const float val)
	{
		m_radius = val;
		circle.setRadius(val);
	}

	__declspec(property(get = get_radius, put = set_radius))
	float radius;

	/* point count property */
	[[nodiscard]] size_t get_point_count() const { return m_pointCount; }

	void set_point_count(const size_t val)
	{
		m_pointCount = val;
		circle.setPointCount(val);
	}

	__declspec(property(get = get_point_count, put = set_point_count))
	size_t point_count;

	/* color property */
	[[nodiscard]] sf::Color get_color() const { return m_color; }

	void set_color(const sf::Color& val)
	{
		m_color = val;
		circle.setFillColor(val);
	}

	__declspec(property(get = get_color, put = set_color))
	sf::Color color;

	/* rotation speed property */
	[[nodiscard]] float get_rotation_speed() const { return m_rotSpeed; }

	void set_rotation_speed(const float val)
	{
		m_rotSpeed = val;
	}

	__declspec(property(get = get_rotation_speed, put = set_rotation_speed))
	float rotation_speed;
};
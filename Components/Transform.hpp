#pragma once

#include "Vec2.hpp"

/*
 * Transform class
 * m_dir: direction which contains normalized velocity
 * m_spd: absolute float value which contains 
 */

class Transform
{
	Vec2  m_dir = {0.f, 0.f};
	float m_spd = 0.f;
	Vec2  m_vel = {0.f, 0.f};

public:
	explicit Transform(const Vec2& vel) { set_velocity(vel); }

	[[nodiscard]] Vec2  get_direction() const { return m_dir; }
	void                set_direction(const Vec2& val);
	[[nodiscard]] float get_speed() const { return m_spd; }
	void                set_speed(float val);
	[[nodiscard]] Vec2  get_velocity() const { return m_vel; }
	void                set_velocity(const Vec2& val);

	static void bounce_horizontal(Transform& obj);
	static void bounce_vertical(Transform& obj);
	static void bounce_both(Transform& obj);

	__declspec(property(get = get_direction, put = set_direction))
	Vec2 direction;
	__declspec(property(get = get_speed, put = set_speed))
	float speed;
	__declspec(property(get = get_velocity, put = set_velocity))
	Vec2 velocity;
	float friction;
};

inline void Transform::set_direction(const Vec2& val)
{
	m_dir = val.normalized();
	m_vel = val * m_spd;
}

inline void Transform::set_speed(const float val)
{
	m_spd = val;
	m_vel = m_dir * val;
}

inline void Transform::set_velocity(const Vec2& val)
{
	m_vel = val;
	m_spd = val.length();
	m_dir = val.normalized();
}

inline void Transform::bounce_horizontal(Transform& obj)
{
	obj.m_dir.x = -obj.m_dir.x;
	obj.m_vel.x = -obj.m_vel.x;
}

inline void Transform::bounce_vertical(Transform& obj)
{
	obj.m_dir.y = -obj.m_dir.y;
	obj.m_vel.y = -obj.m_vel.y;
}

inline void Transform::bounce_both(Transform& obj)
{
	bounce_horizontal(obj);
	bounce_vertical(obj);
}
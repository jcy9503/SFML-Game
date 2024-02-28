#pragma once

#include <fstream>

/* Global Vector2 (float) class
 * ----------------------------
 * - Useful vector math operations
 * - Operator overloading
 * - Convenient constant values
 * - Global methods for interacting with other classes
 */

struct Vec2
{
	float x = 0.f, y = 0.f;

	Vec2() = default;
	Vec2(const float xin, const float yin) : x(xin), y(yin) {}
	Vec2(Vec2 const&)            = default;
	Vec2(Vec2&&)                 = default;
	~Vec2()                      = default;
	Vec2& operator=(Vec2 const&) = default;
	Vec2& operator=(const sf::Vector2u&);
	Vec2& operator=(Vec2&&) = default;
	Vec2& operator-();

	bool  operator==(const Vec2& rhs) const;
	bool  operator!=(const Vec2& rhs) const;
	bool  operator<(const Vec2& rhs) const;
	bool  operator<=(const Vec2& rhs) const;
	bool  operator>(const Vec2& rhs) const;
	bool  operator>=(const Vec2& rhs) const;
	Vec2  operator+(float rhs) const;
	Vec2  operator+(const Vec2& rhs) const;
	Vec2  operator+(const sf::Vector2f& rhs) const;
	Vec2  operator-(float rhs) const;
	Vec2  operator-(const Vec2& rhs) const;
	Vec2  operator-(const sf::Vector2f& rhs) const;
	Vec2  operator*(float spd) const;
	Vec2  operator/(float rhs) const;
	Vec2& operator+=(float rhs);
	Vec2& operator+=(const Vec2& rhs);
	Vec2& operator+=(const sf::Vector2f& rhs);
	Vec2& operator-=(float rhs);
	Vec2& operator-=(const Vec2& rhs);
	Vec2& operator-=(const sf::Vector2f& rhs);
	Vec2& operator*=(float rhs);
	Vec2& operator/=(float rhs);

	[[nodiscard]] float length() const;
	[[nodiscard]] float dist_to(const Vec2& v) const;
	[[nodiscard]] float dist_to_sqr(const Vec2& v) const;
	void                normalize();
	[[nodiscard]] Vec2  normalized() const;
};

const Vec2 vec2_zero{0.f, 0.f};
const Vec2 vec2_one{1.f, 1.f};
const Vec2 vec2_unit_x{1.f, 0.f};
const Vec2 vec2_unit_y{0.f, 1.f};

inline Vec2& Vec2::operator=(const sf::Vector2u& val)
{
	this->x = static_cast<float>(val.x);
	this->y = static_cast<float>(val.y);
	return *this;
}

inline Vec2& Vec2::operator-()
{
	this->x = -this->x;
	this->y = -this->y;
	return *this;
}

inline bool Vec2::operator==(const Vec2& rhs) const
{
	return std::abs(x - rhs.x) < FLT_EPSILON &&
	       std::abs(y - rhs.y) < FLT_EPSILON;
}

inline bool Vec2::operator!=(const Vec2& rhs) const
{
	return !(*this == rhs);
}

inline bool Vec2::operator<(const Vec2& rhs) const
{
	return x < rhs.x && y < rhs.y;
}

inline bool Vec2::operator<=(const Vec2& rhs) const
{
	return x <= rhs.x && y <= rhs.y;
}

inline bool Vec2::operator>(const Vec2& rhs) const
{
	return x > rhs.x && y > rhs.y;
}

inline bool Vec2::operator>=(const Vec2& rhs) const
{
	return x >= rhs.x && y >= rhs.y;
}

inline Vec2 Vec2::operator+(const float rhs) const
{
	return Vec2{*this} += rhs;
}

inline Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2{*this} += rhs;
}

inline Vec2 Vec2::operator-(const float rhs) const
{
	return Vec2{*this} -= rhs;
}

inline Vec2 Vec2::operator-(const Vec2& rhs) const
{
	return Vec2{*this} -= rhs;
}

inline Vec2 Vec2::operator*(const float spd) const
{
	return Vec2{this->x * spd, this->y * spd};
}

inline Vec2 Vec2::operator/(const float rhs) const
{
	return Vec2{*this} /= rhs;
}

inline Vec2& Vec2::operator+=(const float rhs)
{
	this->x += rhs;
	this->y += rhs;
	return *this;
}

inline Vec2& Vec2::operator+=(const Vec2& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}

inline Vec2& Vec2::operator-=(const float rhs)
{
	this->x -= rhs;
	this->y -= rhs;
	return *this;
}

inline Vec2& Vec2::operator-=(const Vec2& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}

inline Vec2& Vec2::operator*=(const float rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	return *this;
}

inline Vec2& Vec2::operator/=(const float rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	return *this;
}

// Interactions with sf::Vector2f

inline Vec2 Vec2::operator+(const sf::Vector2f& rhs) const
{
	return Vec2{x + rhs.x, y + rhs.y};
}

inline Vec2 Vec2::operator-(const sf::Vector2f& rhs) const
{
	return Vec2{x - rhs.x, y - rhs.y};
}

inline float Vec2::length() const
{
	return dist_to(vec2_zero);
}

inline float Vec2::dist_to(const Vec2& v) const
{
	return sqrtf(dist_to_sqr(v));
}

// for computational optimization
inline float Vec2::dist_to_sqr(const Vec2& v) const
{
	return (v.x - x) * (v.x - x) + (v.y - y) * (v.y - y);
}

inline void Vec2::normalize()
{
	if (const float len = length(); len > FLT_EPSILON)
	{
		*this /= len;
	}
}

inline Vec2 Vec2::normalized() const
{
	if (const float len = length(); len < FLT_EPSILON)
	{
		return vec2_zero;
	}
	else
	{
		return Vec2(*this / len);
	}
}

// Global methods
inline std::ostream& operator<<(std::ostream& os, const Vec2& rhs)
{
	return os << "[" << rhs.x << ", " << rhs.y << "]";
}

inline Vec2 operator-(const Vec2& rhs)
{
	return Vec2{-rhs.x, -rhs.y};
}

inline Vec2 operator+(const float lhs, const Vec2& rhs)
{
	return rhs + lhs;
}

inline Vec2 operator-(const float lhs, const Vec2& rhs)
{
	return rhs - lhs;
}

inline Vec2 operator*(const float lhs, const Vec2& rhs)
{
	return rhs * lhs;
}

inline Vec2 operator/(const float lhs, const Vec2& rhs)
{
	return rhs / lhs;
}

inline sf::Vector2f operator+(const sf::Vector2f lhs, const Vec2& rhs)
{
	return sf::Vector2f{lhs.x + rhs.x, lhs.y + rhs.y};
}
#include "../stdafx.h"
#include "Rand.h"

std::mt19937_64 Rand::m_gen;

void Rand::initialize()
{
	std::random_device rd;
	m_gen.seed(rd());
}

void Rand::seed_change(const size_t seed)
{
	m_gen.seed(seed);
}

int Rand::random(const int min, const int max)
{
	return std::uniform_int_distribution{min, max}(m_gen);
}

float Rand::random(const float min, const float max)
{
	return std::uniform_real_distribution{min, max}(m_gen);
}

Vec2 Rand::random(const Vec2& min, const Vec2& max, const float size)
{
	Vec2 output{0.f, 0.f};
	if (const Vec2 maxTp = max - size; min <= maxTp || min >= maxTp)
	{
		output.x = random(min.x, maxTp.x);
		output.y = random(min.y, maxTp.y);
	}

	return output;
}


sf::Color Rand::random_color()
{
	return sf::Color{
		static_cast<sf::Uint8>(random(0, 255)),
		static_cast<sf::Uint8>(random(0, 255)),
		static_cast<sf::Uint8>(random(0, 255))
	};
}

float Rand::random_speed(const float val)
{
	return random(0.f, val * 2) - val;
}

Vec2 Rand::random_vel()
{
	return Vec2{random_speed(SPEED_MAX), random_speed(SPEED_MAX)};
}

Vec2 Rand::random_pos(const float size)
{
	return random(vec2_zero, window_size, size);
}
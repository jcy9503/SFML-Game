#pragma once

#include <random>

class Rand
{
	Rand()  = default;
	~Rand() = default;

	static std::mt19937_64 m_gen;

public:
	Rand(Rand const&)            = delete;
	Rand(Rand&&)                 = delete;
	Rand& operator=(Rand const&) = delete;
	Rand& operator=(Rand&&)      = delete;

	static void initialize();
	static void seed_change(size_t seed);

	static int   random(int min, int max);
	static float random(float min, float max);
	static Vec2  random(const Vec2& min, const Vec2& max, float size = 0.f);

	static int       random_segments() { return random(SEG_MIN, SEG_MAX); }
	static sf::Color random_color();
	static float     random_speed(float val);
	static Vec2      random_vel();
	static Vec2      random_pos(float size);
};
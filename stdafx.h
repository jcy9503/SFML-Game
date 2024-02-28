#pragma once

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif // IMGUI_DEFINE_MATH_OPERATORS

#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <memory>
#include <string>

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "Components/Vec2.hpp"

// Main rendering window variables
inline sf::RenderWindow window;
inline Vec2             window_size;
inline std::string      window_title = "Lucas-SFML";
inline sf::Clock        delta_clock;
inline float            delta_time;

// Entity definition
#define PLAYER_RADIUS 20.f
#define BULLET_RADIUS 5.f
inline Vec2 enemy_radius{10.f, 30.f};

enum
{
	BULLET_SEG_COUNT = 10,
	PLAYER_SEG_COUNT = 10,
	SEG_MIN          = 3,
	SEG_MAX          = 10,
};

#define SPEED_MAX 500.f
#define ROT_SPEED_MAX 500.f

// Math-related variables
inline float pi_f;

// Global methods

// Color input output stream operator overloading
inline std::ostream& operator<<(std::ostream& os, const sf::Color& val)
{
	os << "[" << val.r << ", " << val.g << ", " << val.b << ", " << val.a << "]";
	return os;
}

inline std::istream& operator>>(std::istream& is, sf::Color& val)
{
	is >> val.r >> val.g >> val.b >> val.a;
	return is;
}

// Handling Error
[[noreturn]] inline void error(const std::string& msg, const int exit_num)
{
	std::cout << msg;
	std::quick_exit(exit_num);
}

// Trimming number to string
inline std::string trimming_number(const int num, const int length)
{
	std::string result = std::to_string(num);
	result.insert(0, length - result.length(), '0');

	return result;
}
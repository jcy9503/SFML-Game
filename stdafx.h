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
#include <xmmintrin.h>

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "Components/Vec2.hpp"

// Main rendering window variables
inline sf::RenderWindow window;
inline Vec2             window_size;
inline std::string      window_title = "Lucas-SFML";
inline sf::Clock        delta_clock;

// Entity definition
#define RADIUS_PLAYER 20.f
#define RADIUS_BULLET 5.f

enum
{
    SEG_MIN = 3,
    SEG_MAX = 10,
};

#define SPEED_MAX 3.f

// Math-related variables
inline float pi_f;

// Global methods
// Predicate function returning whether given value is in between two parameters
template <typename T>
bool value_in_range(T value, T min, T max)
{
    return value >= min && value <= max;
}

// Returns inverse square root
inline float inv_sqrt(const float val)
{
    const __m128 srcRegister = _mm_set1_ps(val);
    const __m128 dstRegister = _mm_rsqrt_ps(srcRegister);
    float        array[4];
    _mm_store_ps(array, dstRegister);
    return array[0];
}

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

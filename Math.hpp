#pragma once
#include <xmmintrin.h>

class Math
{
public:
	inline static const float                         pi_f = std::atan(1.f) * 4;
	inline static std::map<size_t, std::vector<Vec2>> circle_dir;

	static std::vector<Vec2>& circle_dir_calc(size_t dir);
};

inline std::vector<Vec2>& Math::circle_dir_calc(const size_t dir)
{
	if (circle_dir.find(dir) == circle_dir.end())
	{
		circle_dir[dir] = std::vector<Vec2>(dir);
		for (size_t i = 0; i < dir; ++i)
		{
			circle_dir[dir][i] = Vec2(cosf(static_cast<float>(i) *
			                               (2 * pi_f / static_cast<float>(dir))),
			                          sinf(static_cast<float>(i) *
			                               (2 * pi_f / static_cast<float>(dir))));
		}
	}

	return circle_dir.at(dir);
}

namespace math
{
	// Predicate function returning whether given value is in between two parameters
	template <typename T>
	bool value_in_range(T value, T min, T max)
	{
		return value >= min && value <= max;
	}

	// clamp function returning value between min and max if input value is not in
	// range of the two parameters, otherwise it returns value as it is.
	template <typename T>
	T clamp(T value, T min, T max)
	{
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	// linear interpolation function
	template <typename T>
	T lerp(const T& p1, const T& p2, const float d1)
	{
		const float d2 = clamp(d1, 0.f, 1.f);
		return T{p1 * (1 - d2) + p2 * d2};
	}

	// Returns inverse square root
	inline float inv_sqrt(const float val)
	{
		const float squareRoot = sqrt(val);
		return 1.f / squareRoot;
	}

	// Does power procedure based on integer
	inline int power_int(const int base, const int n)
	{
		int result = 1;
		for (int i = 0; i < n; ++i)
		{
			result *= base;
		}

		return result;
	}
}
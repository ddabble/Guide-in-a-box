#pragma once

namespace math
{
	struct Vector
	{
		float x;
		float y;

		constexpr Vector operator+(const Vector& other) const { return { x + other.x, y + other.y }; }

		constexpr Vector operator-(const Vector& other) const { return { x - other.x, y - other.y }; }

		constexpr Vector operator*(const Vector& other) const { return { x * other.x, y * other.y }; }

		constexpr Vector operator/(const Vector& other) const { return { x / other.x, y / other.y }; }

		constexpr void operator+=(const Vector& other) { x += other.x; y += other.y; }

		constexpr void operator-=(const Vector& other) { x -= other.x; y -= other.y; }

		constexpr void operator*=(const Vector& other) { x *= other.x; y *= other.y; }

		constexpr void operator/=(const Vector& other) { x /= other.x; y /= other.y; }
	};
	typedef Vector Point;
}

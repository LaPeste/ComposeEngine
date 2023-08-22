#define _USE_MATH_DEFINES
#include "MathLib.hpp"
#include <math.h>

template <typename T>
T MathLib::DotProduct(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
{
	return a.x * b.x + a.y * b.y;
}

template <typename T>
sf::Vector2<T> MathLib::RotateVector(const sf::Vector2<T>& vectorToRotate, T degrees)
{
	float cos = std::cos(degrees);
	float sin = std::sin(degrees);
	float x = cos * vectorToRotate.x - sin * vectorToRotate.y;
	float y = sin * vectorToRotate.x + cos * vectorToRotate.y;
	return sf::Vector2<T>(x, y);
}

template <typename T>
T MathLib::AngleBetween2Vectors(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
{
	auto magnA = Magnitude(a);
	auto magnB = Magnitude(b);
	if (magnA == 0 || magnB == 0) return 0;

	float radiant = std::acos(DotProduct(a, b) / (magnA * magnB));
	return ToDegrees(radiant);
}

template <typename T>
sf::Vector2<T> MathLib::Normalize(const sf::Vector2<T>& vec)
{
	T magnitude = Magnitude(vec);
	if (magnitude == 0)
	{
		DEBUG_ERROR("You can't normilize a vector of length 0");
		throw 4;
	}
	return sf::Vector2<T>(vec.x / magnitude, vec.y / magnitude);
}

template <typename T>
T MathLib::Magnitude(const sf::Vector2<T>& vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

template <typename T>
T MathLib::ToDegrees(T radiant)
{
	return radiant * 180 / M_PI;
}

template <typename T>
T MathLib::ToRadiants(T degrees)
{
	return degrees * M_PI / 180;
}
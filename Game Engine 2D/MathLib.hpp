#ifndef _MATH_LIB_HPP_
#define _MATH_LIB_HPP_

#include "stdafx.h"
#include <numeric>

class MathLib
{
public:
	template <typename T>
	static inline sf::Vector2<T> RotateVector(const sf::Vector2<T>& vectorToRotate, T degrees);

	template <typename T>
	static inline T DotProduct(const sf::Vector2<T>& a, const sf::Vector2<T>& b);

	template <typename T>
	static sf::Vector2<T> Normalize(const sf::Vector2<T>& vec);

	template <typename T>
	static inline T Magnitude(const sf::Vector2<T>& vec);

	template <typename T>
	static T AngleBetween2Vectors(const sf::Vector2<T>& a, const sf::Vector2<T>& b);

	template <typename T>
	static T ToDegrees(T radiant);

	template <typename T>
	static T ToRadiants(T degrees);
};

#include "MathLib.tpp"

#endif
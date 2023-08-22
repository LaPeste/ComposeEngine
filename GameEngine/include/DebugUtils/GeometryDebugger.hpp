#ifndef _GEOMETRY_DEBUGGER_
#define _GEOMETRY_DEBUGGER_

#include "stdafx.h"
#include <functional>

using DrawingFunction = std::function<void(const sf::Vertex *vertices, std::size_t vertexCount, sf::PrimitiveType type, const sf::RenderStates &states)>;

class GeometryDebugger
{
public:
	static void DrawAllShapes();

	static void DrawLine(const sf::Vector2f & pointA, const sf::Vector2f& pointB, sf::Color color = sf::Color::Red);
	static void DrawRay(const sf::Vector2f & point, const sf::Vector2f& dir, sf::Color color = sf::Color::Red);
	static void DrawCircle(const sf::Vector2f & center, float radius, sf::Color color = sf::Color::Red);
	static void DrawRectangle(const sf::Vector2f & originTopLeft, float width, float height, sf::Color color = sf::Color::Red);

private:
	//! shapes that will be drawn at render time
	static std::vector<std::unique_ptr<std::function<void()>>> m_shapesToDraw;
};

#endif //_GEOMETRY_DEBUGGER_

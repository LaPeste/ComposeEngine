#ifndef _GEOMETRY_DEBUGGER_
#define _GEOMETRY_DEBUGGER_

#include "stdafx.h"
#include <functional>
#include <memory>

using DrawingFunction = std::function<void(const sf::Vertex *vertices, std::size_t vertexCount, sf::PrimitiveType type, const sf::RenderStates &states)>;

class GeometryDebugger
{
public:
	static void DrawAllShapes();

	static void DrawLine(sf::Vector2f pointA, sf::Vector2f pointB, sf::Color color = sf::Color::Red);
	static void DrawRay(sf::Vector2f point, sf::Vector2f dir, sf::Color color = sf::Color::Red);

private:
	//! shapes that will be drawn at render time
	static std::vector<std::unique_ptr<std::function<void()>>> m_shapesToDraw;
};

#endif _GEOMETRY_DEBUGGER_

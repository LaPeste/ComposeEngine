#include "GeometryDebugger.h"
#include "Engine.hpp"
#include "MathLib.hpp"

std::vector<std::unique_ptr<std::function<void()>>> GeometryDebugger::m_shapesToDraw;

void GeometryDebugger::DrawLine(const sf::Vector2f& pointA, const sf::Vector2f& pointB, sf::Color color)
{
	std::unique_ptr<std::function<void()>> drawingFunction = std::make_unique<std::function<void()>>([=]() // capture list = all by copy
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(pointA.x, pointA.y)),
			sf::Vertex(sf::Vector2f(pointB.x, pointB.y))
		};
		line[0].color = color;
		line[1].color = color;

		auto* engineWindow = Engine::GetInstance().GetWindow();
		engineWindow->draw(line, 2, sf::PrimitiveType::Lines);	
	});
	m_shapesToDraw.push_back(std::move(drawingFunction));
}

void GeometryDebugger::DrawRay(const sf::Vector2f& point, const sf::Vector2f& dir, sf::Color color)
{
	DrawLine(point, dir + point, color);
}

void GeometryDebugger::DrawCircle(const sf::Vector2f& center, float radius, sf::Color color)
{
	std::unique_ptr<std::function<void()>> drawingFunction = std::make_unique<std::function<void()>>([=]() // capture list = all by copy
	{
		sf::CircleShape shape(radius);
		shape.setOrigin(radius, radius);
		shape.setPosition(center);
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineThickness(1);
		shape.setOutlineColor(color);
		auto* engineWindow = Engine::GetInstance().GetWindow();
		engineWindow->draw(shape);
	});
	m_shapesToDraw.push_back(std::move(drawingFunction));
}

void GeometryDebugger::DrawAllShapes()
{
	for (auto& function : m_shapesToDraw)
	{
		(*function)();
	}
	m_shapesToDraw.clear();
}

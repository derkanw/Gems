#include "ClassGem.h"
#include "Main.h"

Gem::Gem(float gemHeight, float gemWidth, sf::Color gemColor) //constructor of gem
{
	height = gemHeight; width = gemWidth;
	color = gemColor;
	outline = sf::Color::Black;
}

bool Gem::IsEmpty(void) //check empty gem
{
	if (color == sf::Color::Black)
		return true;
	return false;
}

void Gem::SetEmpty(void) //make gem empty
{
	color = sf::Color::Black;
}

sf::Color Gem::GetColor(void) //returns gem's color
{
	return color;
}

void Gem::SetColor(sf::Color newColor) //assigns new color to gem
{
	color = newColor;
}

void Gem::SetOutline(sf::Color newColor) //setting new color of outline
{
	outline = newColor;
}

void Gem::DrawGem(sf::RenderWindow *window, float x, float y) //drawing the gem on field
{
	sf::RectangleShape shape(sf::Vector2f(width, height));
	shape.setFillColor(color);
	shape.setPosition(x, y);
	shape.setOutlineThickness((height + width) / -40);
	shape.setOutlineColor(outline);
	(*window).draw(shape);
}
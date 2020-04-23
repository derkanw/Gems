#pragma once
#include <SFML/Graphics.hpp>

//the class describes the unit of the playing field - gems
class Gem
{
private:
	float height, width; //gem's sizes
	sf::Color color; //gem's color from field's class color spectre
	sf::Color outline; //gem's outline

public:
	Gem(float gemHeight, float gemWidth, sf::Color gemColor); //constructor of gem

	bool IsEmpty(void); //Check empty gems
	void SetEmpty(void); //make gem empty
	sf::Color GetColor(void); //returns gem's color
	void SetColor(sf::Color newColor); //assigns new color to gem
	void SetOutline(sf::Color newColor); //setting new color of outline


	void DrawGem(sf::RenderWindow* window, float x, float y); //drawing the gem on field
};
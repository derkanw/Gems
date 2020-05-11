#pragma once
#include <SFML/Graphics.hpp>

class Gem //the class describes the unit of the playing field - gems
{
private:
    float height, width; //gem's sizes
    sf::Color color; //gem's color from field's class color spectre
    sf::Color outline; //gem's outline

public:
    Gem(float gemHeight, float gemWidth, sf::Color gemColor); //constructor of gem
    ~Gem(void) {} //destructor of gem

    bool IsEmpty(void); //Check empty gems

    void SetEmpty(void); //make gem empty
    void SetColor(sf::Color newColor); //assigns new color to gem
    void SetOutline(sf::Color newColor); //setting new color of outline

    sf::Color GetColor(void); //returns gem's color

    void DrawGem(std::shared_ptr <sf::RenderWindow> window, float x, float y); //drawing the gem on field
};
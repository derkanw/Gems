#pragma once
#include "ClassGem.h"
#include "Main.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

//Class that keeps gems in matrix
class Field
{
private:
	std::vector <std::vector <Gem>> gemsMatrix; //matrix of gems
	std::array <sf::Color, 6> colorsMatrix = {sf::Color::Blue, sf::Color::Green, sf::Color::Red, sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan}; //matrix of gems' colors
	float height, width; //size of field with gems
	unsigned gemsInRow, gemsInColumn; //number of gems in row and column

public:
	Field(void); //gems' field constructor 

	void GenerateField(void); //filling the field
	void DrawField(sf::RenderWindow *window);//drawing field with gems
	
	void CheckField(unsigned i, unsigned j); //find neighbours of a gem which have the same color
	bool AlreadyChoose(unsigned i, unsigned j); //doesn't allow adding an already checked element to the vector
	void DeleteChoosedGems(void); //delete compination of gems which have the same color
	void FindGemsReiteration(void); //àind and delete gems' reiteration
};
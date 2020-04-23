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

	bool GemsDrop(void); //upper gems drop for filling out the field
	void FieldRefilling(void); //refilling empty cells by new gems

	void SetHighlight(unsigned x, unsigned y, sf::Color newColor); //setting gem's highlighter
	void GemsSwap(unsigned x1, unsigned y1, unsigned x2, unsigned y2); //swapping two gems

};
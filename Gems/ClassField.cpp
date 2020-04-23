#include "ClassField.h"
#include "Main.h"
#include <cstdlib>

Field::Field(void) //gems' field constructor
{
	height = (float)fieldWindowHeight;
	width = (float)fieldWindowWidth;
	gemsInRow = numberGemsInRow;
	gemsInColumn = numberGemsInColumn;
	GenerateField();
}

void Field::GenerateField(void) //filling the field
{
	for (unsigned i = 0; i < gemsInColumn; i++)
	{
		std::vector <Gem> temp;
		for (unsigned j = 0; j < gemsInRow; j++)
		{
			Gem gem((float)(height / gemsInColumn), (float)(width / gemsInRow), colorsMatrix[rand() % colorsMatrix.size()]);
			temp.push_back(gem);
		}
		gemsMatrix.push_back(temp);
		temp.~vector();
	}
}

void Field::DrawField(sf::RenderWindow* window) //drawing field with gems
{
	for (unsigned i = 0; i < gemsInColumn; i++)
		for (unsigned j = 0; j < gemsInRow; j++)
			gemsMatrix[i][j].DrawGem(window, (float)(j * fieldWindowWidth) / gemsInRow+offsetWidth, (float)(i * fieldWindowHeight) / gemsInColumn+offsetHeight);
}
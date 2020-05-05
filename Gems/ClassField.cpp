#include <string>
#include <cstdlib>
#include "ClassField.h"
#include "Main.h"

Field::Field(void) //gems' field constructor
{

	height = (float)fieldWindowHeight;
	width = (float)fieldWindowWidth;
	gemsInRow = numberGemsInRow;
	gemsInColumn = numberGemsInColumn;
	sf::Texture texture;
	for (unsigned i = 0; i < 2; i++)
	{
		texture.loadFromFile("Textures/" + std::to_string(i) + ".png");
		textureMatrix.push_back(texture);
	}
	GenerateField();
}

bool Field::GemIsEmpty(unsigned i, unsigned j)
{
	return gemsMatrix[i][j].IsEmpty();
}

void Field::SetNewGemsColor(std::vector <std::array <unsigned, 2>> paintedGems, unsigned i, unsigned j)
{
	for (unsigned k = 0; k < paintedGems.size(); k++)
		gemsMatrix[paintedGems[k][0]][paintedGems[k][1]].SetColor(gemsMatrix[i][j].GetColor());
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

sf::Texture* Field::GetTexture(unsigned type)
{
	return &textureMatrix[type];
}

unsigned Field::GetGemsInRow(void)
{
	return gemsInRow;
}

unsigned Field::GetGemsInColumn(void)
{
	return gemsInColumn;
}

std::vector <std::array <unsigned, 2>> Field::GetReiterationVector(void)
{
	return reiteration;
}
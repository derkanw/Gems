#include <iostream>
#include "Bonus.h"
#include "Main.h"

Bonus::Bonus(unsigned newX, unsigned newY, unsigned newType)
{
	x = newX;
	y = newY;
	type = newType;
}

void Bonus::DrawBonus(sf::RenderWindow* window, std::shared_ptr<Field> field)
{
	sf::RectangleShape shape(sf::Vector2f((float)fieldWindowWidth / (float)field->GetGemsInRow(), (float)fieldWindowHeight / (float)field->GetGemsInColumn()));
	shape.setPosition((float)(x * fieldWindowWidth) / (float)field->GetGemsInRow() + offsetWidth, (float)(y * fieldWindowHeight) / (float)field->GetGemsInColumn() + offsetHeight);
	shape.setTexture(field->GetTexture(type));
	(*window).draw(shape);
}

void Bomb::Trigger(std::shared_ptr<Field> field)
{
	std::vector <std::array<unsigned, 2>> bombedGems;
	bombedGems.push_back({ y, x });
	
	for (unsigned i = 0; i < bombedNumber - 1; i++)
		bombedGems.push_back({ rand() % field->GetGemsInColumn(),rand() % field->GetGemsInRow() });
	field->DeleteChoosedGems(bombedGems);
}

void Painter::Trigger(std::shared_ptr<Field> field)
{
	std::vector <std::array<unsigned, 2>> paintedGems;

	for (unsigned i = 0; i < paintedNumber; i++)
	{
		unsigned randomX, randomY;
		do
		{
			randomX = x + (rand() % (paintedRadius - 1) + 2) * (int)pow(-1, rand() % 2);
			randomY = y + (rand() % (paintedRadius - 1) + 2) * (int)pow(-1, rand() % 2);
		}
		while ((randomX >= field->GetGemsInRow()) || (randomY >= field->GetGemsInColumn()) || (field->GemIsEmpty(randomY, randomX)) || (field->AlreadyChoose(randomY, randomX, paintedGems)));
		paintedGems.push_back({ randomY, randomX });
	}

	field->SetNewGemsColor(paintedGems, y, x);
}
#include "Bonus.h"
#include "Main.h"

Bonus::Bonus(unsigned newX, unsigned newY)
{
	x = newX;
	y = newY;
}

void Bomb::Trigger(std::shared_ptr<Field> field)
{
	std::vector <std::array<unsigned, 2>> bombedGems;
	bombedGems.push_back({ x, y });
	
	for (unsigned i = 0; i < bombedNumber - 1; i++)
		bombedGems.push_back({ rand() % field->GetGemsInRow(), rand() % field->GetGemsInColumn() });
	field->DeleteChoosedGems(bombedGems);
}
#include "ClassField.h"

bool Field::GemsDrop(void) //upper gems drop for filling out the field
{
	bool drop = false;
	for (unsigned i=0; i<gemsInColumn-1;i++)
		for (unsigned j = 0; j < gemsInRow; j++)
			if ((!gemsMatrix[i][j].IsEmpty()) && (gemsMatrix[i + 1][j].IsEmpty()))
			{
				gemsMatrix[i + 1][j].SetColor(gemsMatrix[i][j].GetColor());
				gemsMatrix[i][j].SetEmpty();
				drop = true;
			}
	return drop;
}

void Field::FieldRefilling(void) //refilling empty cells by new gems
{
	for (unsigned i = 0; i < gemsInColumn; i++)
		for (unsigned j = 0; j < gemsInRow; j++)
			if (gemsMatrix[i][j].IsEmpty())
				gemsMatrix[i][j].SetColor(colorsMatrix[rand() % colorsMatrix.size()]);
}
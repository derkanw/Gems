#include "ClassField.h"

std::vector <std::array <unsigned, 2>> reiteration; //vector of gems' coordinate the same color

void Field::CheckField(unsigned i, unsigned j) //find neighbours of a gem which have the same color
{
	if (gemsMatrix[i][j].IsEmpty()) //skip empty gems
		return;

	if ((i != 0) && (gemsMatrix[i][j].GetColor() == gemsMatrix[i-1][j].GetColor()) && (!AlreadyChoose(i-1, j))) //check top element
	{
		reiteration.push_back({ i-1, j });
		CheckField(i-1, j);
	}

	if ((j != gemsInRow - 1) && (gemsMatrix[i][j].GetColor() == gemsMatrix[i][j + 1].GetColor()) && (!AlreadyChoose(i, j + 1))) //check right element
	{
		reiteration.push_back({ i, j + 1 });
		CheckField(i, j + 1);
	}

	if ((i != gemsInColumn-1) && (gemsMatrix[i][j].GetColor() == gemsMatrix[i+1][j].GetColor()) && (!AlreadyChoose(i+1, j))) //check buttom element
	{
		reiteration.push_back({ i + 1, j });
		CheckField(i + 1, j);
	}

	if ((j != 0) && (gemsMatrix[i][j].GetColor() == gemsMatrix[i][j-1].GetColor()) && (!AlreadyChoose(i, j-1))) //check left element
	{
		reiteration.push_back({ i, j-1 });
		CheckField(i, j-1);
	}
}

bool Field::AlreadyChoose(unsigned i, unsigned j) //doesn't allow adding an already checked element to the vector
{
	for (unsigned k = 0; k < reiteration.size(); k++)
		if ((i == reiteration[k][0]) && (j == reiteration[k][1]))
			return true;
	return false;
}

void Field::DeleteChoosedGems(void) //delete compination of gems which have the same color
{
	for (unsigned k = 0; k < reiteration.size(); k++)
		gemsMatrix[reiteration[k][0]][reiteration[k][1]].SetEmpty();
}

void Field::FindGemsReiteration(void) //find and delete gems' reiteration
{
	reiteration.clear();
	for (unsigned i = 0; i < gemsInColumn; i++)
	{
		for (unsigned j = 0; j < gemsInRow; j++)
		{
			reiteration.push_back({ i, j });
			CheckField(i, j);
			if (reiteration.size() > 2)
				break;
			else
				if (!reiteration.empty())
					reiteration.clear();
		}
		if (reiteration.size() > 2)
			break;
	}

	DeleteChoosedGems();
}


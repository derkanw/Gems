#include "ClassField.h"

bool Field::NeighborIsGood(unsigned i, unsigned j, unsigned neighborI, unsigned neighborJ) //support function to check neighbors of gem
{
    bool colorIsGood = false, notChoosed = false;

    if (gemsMatrix[i][j].GetColor() == gemsMatrix[neighborI][neighborJ].GetColor())
        colorIsGood = true;
    if (!AlreadyChoose(neighborI, neighborJ, reiteration))
        notChoosed = true;

    if (colorIsGood & notChoosed)
        return true;
    else
        return false;
}

void Field::CheckField(unsigned i, unsigned j) //find neighbours of a gem which have the same color
{
    if (gemsMatrix[i][j].IsEmpty()) //skip empty gems
        return;

    if ((i != 0) && (NeighborIsGood(i, j, i - 1, j))) //check top element
    {
        reiteration.push_back({ i - 1, j });
        CheckField(i - 1, j);
    }

    if ((j != gemsInRow - 1) && (NeighborIsGood(i, j, i, j + 1))) //check right element
    {
        reiteration.push_back({ i, j + 1 });
        CheckField(i, j + 1);
    }

    if ((i != gemsInColumn - 1) && (NeighborIsGood(i, j, i + 1, j))) //check buttom element
    {
        reiteration.push_back({ i + 1, j });
        CheckField(i + 1, j);
    }

    if ((j != 0) && (NeighborIsGood(i, j, i, j - 1))) //check left element
    {
        reiteration.push_back({ i, j - 1 });
        CheckField(i, j - 1);
    }
}

bool Field::AlreadyChoose(unsigned i, unsigned j, std::vector <std::array <unsigned, 2>> checkVector) /*
doesn't allow adding an already checked element to the vector*/
{
    for (unsigned k = 0; k < checkVector.size(); k++)
        if ((i == checkVector[k][0]) && (j == checkVector[k][1]))
            return true;
    return false;
}

unsigned Field::DeleteChoosedGems(std::vector <std::array <unsigned, 2>> forDeletion) //delete compination of gems which have the same color
{
    for (unsigned k = 0; k < forDeletion.size(); k++)
        gemsMatrix[forDeletion[k][0]][forDeletion[k][1]].SetEmpty();

     return (unsigned)forDeletion.size();
}

unsigned Field::FindGemsReiteration(void) //find and delete gems' reiteration
{
    bool result = false;

    reiteration.clear();

    for (unsigned i = 0; i < gemsInColumn; i++)
    {
        for (unsigned j = 0; j < gemsInRow; j++)
        {
            reiteration.push_back({ i, j });
            CheckField(i, j);

            if (reiteration.size() > 2)
            {
                result = true;
                break;
            }
            else
                if (!reiteration.empty())
                    reiteration.clear();
        }

        if (reiteration.size() > 2)
            break;
    }

    return DeleteChoosedGems(reiteration);
}
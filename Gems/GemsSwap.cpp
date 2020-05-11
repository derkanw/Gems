#include "ClassField.h"

void Field::SetHighlight(unsigned x, unsigned y, sf::Color newColor) //setting gem's highlighter
{
    if (!gemsMatrix[y][x].IsEmpty())
        gemsMatrix[y][x].SetOutline(newColor);
}

void Field::GemsSwap(unsigned x1, unsigned y1, unsigned x2, unsigned y2) //swapping two gems
{
    sf::Color color1, color2;
    color1 = gemsMatrix[y1][x1].GetColor();
    color2 = gemsMatrix[y2][x2].GetColor();

    gemsMatrix[y1][x1].SetColor(color2);
    gemsMatrix[y2][x2].SetColor(color1);
}
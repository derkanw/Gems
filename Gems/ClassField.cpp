#include <string>
#include <cstdlib>
#include "ClassField.h"

Field::Field(float fieldWindowHeight, float fieldWindowWidth, unsigned numberGemsInRow, unsigned numberGemsInColumn) //gems' field constructor
{
    height = fieldWindowHeight;
    width = fieldWindowWidth;
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

bool Field::GemIsEmpty(unsigned i, unsigned j) //check gem's emptiness
{
    return gemsMatrix[i][j].IsEmpty();
}

void Field::SetNewGemsColor(std::vector <std::array <unsigned, 2>> paintedGems, unsigned i, unsigned j) /*
    change color of choosed gems according to matching gem's color*/
{
    for (unsigned k = 0; k < paintedGems.size(); k++)
        gemsMatrix[paintedGems[k][0]][paintedGems[k][1]].SetColor(gemsMatrix[i][j].GetColor());
}

void Field::GenerateField(void) //filling the field
{
    float gemHeight = (float)(height / gemsInColumn), gemWidth = (float)(width / gemsInRow);

    for (unsigned i = 0; i < gemsInColumn; i++)
    {
        std::vector <Gem> temp;

        for (unsigned j = 0; j < gemsInRow; j++)
        {
            Gem gem(gemHeight, gemWidth, colorsMatrix[rand() % colorsMatrix.size()]);
            temp.push_back(gem);
        }

        gemsMatrix.push_back(temp);
        temp.~vector();
    }
}

void Field::DrawField(std::shared_ptr <sf::RenderWindow> window, float offsetHeight, float offsetWidth) //drawing field with gems
{
    float posX, posY;

    for (unsigned i = 0; i < gemsInColumn; i++)
        for (unsigned j = 0; j < gemsInRow; j++)
        {
            posX = (float)(j * width) / gemsInRow + offsetWidth;
            posY = (float)(i * height) / gemsInColumn + offsetHeight;
            gemsMatrix[i][j].DrawGem(window, posX, posY);
        }
}

sf::Texture* Field::GetTexture(unsigned type) //getting texture matched with the type of bonus
{
    return &textureMatrix[type];
}

unsigned Field::GetGemsInRow(void) //getting number of gems in field's row
{
    return gemsInRow;
}

unsigned Field::GetGemsInColumn(void) //getting number of gems in field's column
{
    return gemsInColumn;
}

std::vector <std::array <unsigned, 2>> Field::GetReiterationVector(void) //getting vector, which keeps gems' combination
{
    return reiteration;
}

float Field::GetFieldHeight(void) //getting height of field
{
    return height;
}

float Field::GetFieldWidth(void) //getting width of field
{
    return width;
}
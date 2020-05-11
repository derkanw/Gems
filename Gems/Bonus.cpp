#include <iostream>
#include "Bonus.h"

Bonus::Bonus(unsigned newX, unsigned newY, unsigned newType) //default bonus constructor
{
    x = newX;
    y = newY;
    type = newType;
}

void Bonus::DrawBonus(std::shared_ptr <sf::RenderWindow> window, std::shared_ptr<Field> field, float offsetHeight, float offsetWidth)/*
drawing bomb or painter with matching texture*/
{
    float width = field->GetFieldWidth() / (float)field->GetGemsInRow();
    float height = field->GetFieldHeight() / (float)field->GetGemsInColumn();

    float posX = (float)(x * field->GetFieldWidth()) / (float)field->GetGemsInRow() + offsetWidth;
    float posY = (float)(y * field->GetFieldHeight()) / (float)field->GetGemsInColumn() + offsetHeight;

    sf::RectangleShape shape(sf::Vector2f(width, height));
    shape.setPosition(posX, posY);
    shape.setTexture(field->GetTexture(type));
    window->draw(shape);
}

unsigned Bomb::Trigger(std::shared_ptr<Field> field) //bomb triggering
{
    std::vector <std::array<unsigned, 2>> bombedGems;
    bombedGems.push_back({ y, x });

    for (unsigned i = 0; i < bombedNumber - 1; i++)
        bombedGems.push_back({ rand() % field->GetGemsInColumn(), rand() % field->GetGemsInRow() });

    return field->DeleteChoosedGems(bombedGems);
}

unsigned Painter::Trigger(std::shared_ptr<Field> field) //painter triggering
{
    std::vector <std::array<unsigned, 2>> paintedGems;

    unsigned randomX, randomY;
    bool empty, choosing;
    for (unsigned i = 0; i < paintedNumber; i++)
    {
        do
        {
            randomX = x + (rand() % (paintedRadius - 1) + 2) * (int)pow(-1, rand() % 2);
            randomY = y + (rand() % (paintedRadius - 1) + 2) * (int)pow(-1, rand() % 2);
            empty = field->GemIsEmpty(randomY, randomX);
            choosing = field->AlreadyChoose(randomY, randomX, paintedGems);

        } while ((randomX >= field->GetGemsInRow()) || (randomY >= field->GetGemsInColumn()) || (empty) || (choosing));

        paintedGems.push_back({ randomY, randomX });
    }

    field->SetNewGemsColor(paintedGems, y, x);
    return 0;
}
#include <string>
#include "ClassGameLoop.h"
#define TARGET_SCORE 100
#define CHANCE_OF_BONUS 5

GameLoop::GameLoop(void) //constructor
{
    userWindowHeight = 600;
    userWindowWidth = 500;
    fieldWindowHeight = 480;
    fieldWindowWidth = 480;
    numberGemsInRow = 5;
    numberGemsInColumn = 6;
    offsetHeight = 0;
    offsetWidth = 0;

    score = 0;

    drop = false;
    secondClick = false;
    swap = false;
    firstswap = false;

    gem1X = 0;
    gem1Y = 0;
    gem2X = 0;
    gem2Y = 0;

    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(userWindowWidth, userWindowHeight), "Gems");
    window->setFramerateLimit(3);

    field = std::make_shared<Field>((float)fieldWindowHeight, (float)fieldWindowWidth, numberGemsInRow, numberGemsInColumn);
}

void GameLoop::FieldOffset(void) //defines offsets of gem to move field with gems around the window
{
    float minOffset;
    offsetHeight = (float)(userWindowHeight - fieldWindowHeight);
    offsetWidth = (float)(userWindowWidth - fieldWindowWidth);
    minOffset = offsetWidth / 2;
    if (offsetHeight / 2 < minOffset)
        minOffset = offsetHeight / 2;
    offsetWidth = minOffset;
    offsetHeight -= offsetWidth;
}

void GameLoop::SpawnBonus(void) //spawn bonus (bomb or painter) with some chance in radius of 3 gems around the matching gem
{
    unsigned bonusX, bonusY;
    for (unsigned k = 0; k < (field->GetReiterationVector()).size(); k++)
        if (rand() % 100 < CHANCE_OF_BONUS)
        {
            do
            {
                bonusX = field->GetReiterationVector()[k][1] + (rand() % 3 + 1) * (int)pow(-1, rand() % 2);
                bonusY = field->GetReiterationVector()[k][0] + (rand() % 3 + 1) * (int)pow(-1, rand() % 2);

            } while ((bonusX >= field->GetGemsInRow()) || (bonusY >= field->GetGemsInColumn()) || (field->GemIsEmpty(bonusY, bonusX)));

            switch (rand() % 2)
            {
            case 0:
                bonusesMatrix.push_back(std::make_shared<Bomb>(bonusX, bonusY));
                break;
            case 1:
                bonusesMatrix.push_back(std::make_shared<Painter>(bonusX, bonusY));
                break;
            }
        }
}

void GameLoop::GemsDeletion(void) //delition gems' combinations
{
    unsigned addition = 0;
    if (!drop)
    {
        addition = field->FindGemsReiteration();
        if ((swap) & (addition == 0))
            field->GemsSwap(gem2X, gem2Y, gem1X, gem1Y);
        score += addition;
    }

    swap = false;

    drop = field->GemsDrop();
    if (!drop)
    {
        field->FieldRefilling();
        SpawnBonus();
    }
}

void GameLoop::BonusTrigger(void) //bonus triggering
{
    for (unsigned k = 0; k < bonusesMatrix.size(); k++)
        score += bonusesMatrix[k]->Trigger(field);

    if (bonusesMatrix.size() > 0)
    {
        drop = true;
        bonusesMatrix.clear();
    }
}

bool GemsIsGood(unsigned gem1X, unsigned gem1Y, unsigned gem2X, unsigned gem2Y) //check coordinates of gems
{
    bool radiusCheck = false;
    bool diagonalCheck = false;

    if ((abs((int)gem2X - (int)gem1X) <= 1) && (abs((int)gem2Y - (int)gem1Y) <= 1))
        radiusCheck = true;

    if (!((abs((int)gem2X - (int)gem1X) == 1) && (abs((int)gem2Y - (int)gem1Y) == 1)))
        diagonalCheck = true;

    return (radiusCheck & diagonalCheck);
}

void GameLoop::SelectFirstGem(float xInMatrix, float yInMatrix) //the first click on a gem
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //the first click
    {
        sf::Vector2i localPosition1 = sf::Mouse::getPosition(*window);

        gem1X = (unsigned)((float)localPosition1.x / xInMatrix - (offsetWidth / xInMatrix));
        gem1Y = (unsigned)((float)localPosition1.y / yInMatrix - (offsetHeight / yInMatrix));

        field->SetHighlight(gem1X, gem1Y, sf::Color::White);
        secondClick = true;
    }
}

void GameLoop::CancelClick(void) //cancel click on the gem
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        field->SetHighlight(gem1X, gem1Y, sf::Color::Black);
        secondClick = false;
    }
}

void GameLoop::GemsPermutation(void) //realizes changing of two matching gems' color
{
    if (GemsIsGood(gem1X, gem1Y, gem2X, gem2Y))
    {
        field->GemsSwap(gem1X, gem1Y, gem2X, gem2Y);
        field->SetHighlight(gem1X, gem1Y, sf::Color::Black);
        field->SetHighlight(gem2X, gem2Y, sf::Color::Black);

        swap = true;
        firstswap = true;
    }
}

void GameLoop::SelectSecondGem(float xInMatrix, float yInMatrix) //the second click on anther gem
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //the second click
    {
        sf::Vector2i localPosition2 = sf::Mouse::getPosition(*window);
        gem2X = (unsigned)((float)localPosition2.x / xInMatrix - (offsetWidth / xInMatrix));
        gem2Y = (unsigned)((float)localPosition2.y / yInMatrix - (offsetHeight / yInMatrix));

        GemsPermutation();
        secondClick = false;
    }
    else
        CancelClick();
}

void GameLoop::Swap(void) //changing position of two matching gems
{
    float xInMatrix = (float)fieldWindowWidth / (float)numberGemsInRow;
    float yInMatrix = (float)fieldWindowHeight / (float)numberGemsInColumn;

    if (!drop)
        if (!secondClick)
            SelectFirstGem(xInMatrix, yInMatrix);
        else
            SelectSecondGem(xInMatrix, yInMatrix);
}

void GameLoop::DrawGameLoop(void) //drawing all figure on the field
{
    field->DrawField(window, offsetHeight, offsetWidth);

    for (unsigned k = 0; k < bonusesMatrix.size(); k++)
        bonusesMatrix[k]->DrawBonus(window, field, offsetHeight, offsetWidth);
}

void GameLoop::CreateText(void) //showing score
{
    sf::Font font;
    font.loadFromFile("Textures/font.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setPosition(offsetWidth, offsetHeight / 3);

    if (!firstswap)
        score = 0;
    text.setString("Score: " + std::to_string(score));
    window->draw(text);
}

void GameLoop::Win(void) //if the player won
{
    sf::Texture texture;
    texture.loadFromFile("Textures/win.png");

    sf::RectangleShape shape(sf::Vector2f((float)fieldWindowWidth, (float)fieldWindowHeight));
    shape.setPosition((float)offsetWidth, (float)offsetHeight);
    shape.setTexture(&texture);

    window->draw(shape);
    window->display();

    sf::Clock timer;
    while (timer.getElapsedTime().asSeconds() < 3);

    window->close();
}

void GameLoop::Start(void) //all the gameplay
{
    while (window->isOpen())
    {
        sf::Event event; //if window close
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();

        BonusTrigger();
        GemsDeletion();
        Swap();
        DrawGameLoop();
        CreateText();

        if (score >= TARGET_SCORE)
        {
            Win();
            break;
        }

        window->display();
    }
}
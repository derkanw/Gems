#include "Main.h"
#include "Bonus.h"

unsigned userWindowHeight = 600, userWindowWidth = 500; //size of window
unsigned fieldWindowHeight = 480, fieldWindowWidth = 480; //size of field with gems
unsigned numberGemsInRow = 5, numberGemsInColumn = 6; //number of gems in row and column
float offsetHeight, offsetWidth; //substruction between size of user's window and field's size

void SpawnBonus(std::vector<std::shared_ptr<Bonus>>* bonusesMatrix, std::shared_ptr <Field> field)
{
	unsigned bonusX, bonusY;
	for (unsigned k = 0; k < (field->GetReiterationVector()).size(); k++)
		if (rand() % 100 < 50)
		{
			do
			{
				bonusX = field->GetReiterationVector()[k][1] + (rand() % 3 + 1) * (int)pow(-1, rand() % 2);
				bonusY = field->GetReiterationVector()[k][0] + (rand() % 3 + 1) * (int)pow(-1, rand() % 2);
			}
			while ((bonusX >= field->GetGemsInRow()) || (bonusY >= field->GetGemsInColumn())||(field->GemIsEmpty(bonusY, bonusX)));

			switch (rand() % 2) 
			{
			case 0:
				bonusesMatrix->push_back(std::make_shared<Bomb>(bonusX, bonusY));
				break;
			case 1:
				bonusesMatrix->push_back(std::make_shared<Painter>(bonusX, bonusY));
				break;
			}
		}
}

void FieldOffset(void) //defines offsets of gem to move field with gems around the window
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

int main(void)
{
	srand((unsigned)time(0)); //generation of random gems' colors

	bool drop = false; //shows whether the fall of gems continues
	bool secondClick = false; //show whether the second gem selected 

	unsigned gem1X, gem1Y, gem2X, gem2Y; //keeps coordinates of two gems

	sf::RenderWindow window(sf::VideoMode(userWindowWidth, userWindowHeight), "Gems");
	std::shared_ptr <Field> field(new Field());
	std::vector<std::shared_ptr<Bonus>> bonusesMatrix;

	FieldOffset();
	while (window.isOpen())
	{
		sf::Event event; //if window close
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		for (unsigned k = 0; k < bonusesMatrix.size(); k++)
			bonusesMatrix[k]->Trigger(field);

		if (bonusesMatrix.size() > 0)
		{
			drop = true;
			bonusesMatrix.clear();
		}

		//delition gems' combinations
		if (drop == false)
		{
			field->FindGemsReiteration();
			//SpawnBonus(&bonusesMatrix, field);
		}
		drop = field->GemsDrop();
		if (drop == false)
		{
			field->FieldRefilling();
			SpawnBonus(&bonusesMatrix, field);
		}

		//swap gems
		if (drop==false)
			if (secondClick == false)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2i localPosition1 = sf::Mouse::getPosition(window);
					gem1X = (unsigned)((float)localPosition1.x / ((float)fieldWindowWidth/ (float)numberGemsInRow)-(offsetWidth/((float)fieldWindowWidth/(float)numberGemsInRow)));
					gem1Y = (unsigned)((float)localPosition1.y / ((float)fieldWindowHeight / (float)numberGemsInColumn) - (offsetHeight / ((float)fieldWindowHeight / (float)numberGemsInColumn)));
					field->SetHighlight(gem1X, gem1Y, sf::Color::White);
					secondClick = true;
				}
			}
			else
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2i localPosition2 = sf::Mouse::getPosition(window);
						gem2X = (unsigned)((float)localPosition2.x / ((float)fieldWindowWidth / (float)numberGemsInRow) - (offsetWidth / ((float)fieldWindowWidth / (float)numberGemsInRow)));
						gem2Y = (unsigned)((float)localPosition2.y / ((float)fieldWindowHeight / (float)numberGemsInColumn) - (offsetHeight / ((float)fieldWindowHeight / (float)numberGemsInColumn)));
						//field.SetHighlight(gem2X, gem2Y, sf::Color::Green);
						if ((abs((int)gem2X - (int)gem1X) <= 1) && (abs((int)gem2Y - (int)gem1Y) <= 1) && !((abs((int)gem2X - (int)gem1X) == 1) && (abs((int)gem2Y - (int)gem1Y) == 1)))
						{
							field->GemsSwap(gem1X, gem1Y, gem2X, gem2Y);
							field->SetHighlight(gem1X, gem1Y, sf::Color::Black);
							field->SetHighlight(gem2X, gem2Y, sf::Color::Black);
						}
						secondClick = false;
				}
				else
					if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
					{
						field->SetHighlight(gem1X, gem1Y, sf::Color::Black);
						secondClick = false;
					}

		//drawing field
		field->DrawField(&window);
		for (unsigned k = 0; k < bonusesMatrix.size(); k++)
			bonusesMatrix[k]->DrawBonus(&window, field);

		sf::Clock timer; //time between frames
		while (timer.getElapsedTime().asSeconds() < 1);

		window.display();
	}

	return 0;
}
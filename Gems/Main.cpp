#include "Main.h"

unsigned userWindowHeight = 600, userWindowWidth = 500; //size of window
unsigned fieldWindowHeight = 380, fieldWindowWidth = 480; //size of field with gems
unsigned numberGemsInRow = 6, numberGemsInColumn = 5; //number of gems in row and column

int main(void)
{
	srand((unsigned)time(0)); //generation of random gems' colors
	
	sf::RenderWindow window(sf::VideoMode(userWindowWidth, userWindowHeight), "Gems");
	Field field;

	while (window.isOpen())
	{
		sf::Event event; //if window close
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		field.FindGemsReiteration();

		//drawing field
		field.DrawField(&window);

		//time between frames
		sf::Clock timer;
		while (timer.getElapsedTime().asSeconds() < 0.25);

		window.display();
	}

	return 0;
}
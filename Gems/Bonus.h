#pragma once
#include <memory>
#include "ClassField.h"

class Bonus //abstract class for game bonuses
{
protected:
	unsigned x, y, type;

public:
	Bonus(unsigned newX, unsigned newY, unsigned newType); //default constructor
	~Bonus(void) {} //default destructor

	virtual void Trigger(std::shared_ptr<Field> field) = 0;
	void DrawBonus(sf::RenderWindow* window, std::shared_ptr<Field> field); 
};

class Bomb :public Bonus
{
private:
	unsigned bombedNumber = 5;

public:
	Bomb(unsigned newX, unsigned newY) :Bonus(newX, newY, 0) {} //constructor
	void Trigger(std::shared_ptr<Field> field) override;
};

class Painter :public Bonus
{
private:
	unsigned paintedNumber = 2, paintedRadius = 3;

public:
	Painter(unsigned newX, unsigned newY) :Bonus(newX, newY, 1) {} //constructor
	void Trigger(std::shared_ptr<Field> field) override;
};
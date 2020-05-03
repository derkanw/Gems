#pragma once
#include "ClassField.h"

class Bonus //abstract class for game bonuses
{
protected:
	unsigned x, y;

public:
	Bonus(unsigned newX, unsigned newY); //default constructor
	~Bonus(void) {}; //default destructor

	virtual void Trigger(std::shared_ptr<Field> field) {};
	//void DrawBonus(std::shared_ptr<Field> field); 
};

class Bomb :public Bonus
{
private:
	unsigned bombedNumber = 5; //i need this?

public:
	Bomb(void) {}; //constructor
	void Trigger(std::shared_ptr<Field> field) override;
};

class Painter :public Bonus
{
private:
	unsigned paintedNumber = 2, paintedRadius = 3;

public:
	Painter(void) {}; //constructor
	//void Trigger(std::shared_ptr<Field> field) override;
};
#pragma once
#include <memory>
#include "ClassField.h"

class Bonus //abstract class for game bonuses
{
protected:
    unsigned x, y; //position of bonus
    unsigned type; //type of bonus: "0"-bomb or "1"-painter

public:
    Bonus(unsigned newX, unsigned newY, unsigned newType); //default bonus constructor
    ~Bonus(void) {} //default bonus destructor

    virtual unsigned Trigger(std::shared_ptr<Field> field) = 0; //virtual bonus triggering method
    void DrawBonus(std::shared_ptr <sf::RenderWindow> window, std::shared_ptr<Field> field, float offsetHeight, float offsetWidth); /*
    drawing bomb or painter with matching texture*/
};

class Bomb :public Bonus //child class of bonus, which destroys five gems on the field
{
private:
    unsigned bombedNumber = 5; //number of gems for destruction

public:
    Bomb(unsigned newX, unsigned newY) :Bonus(newX, newY, 0) {} //bomb constructor with sending position of bonus and type of it
    unsigned Trigger(std::shared_ptr<Field> field) override; //bomb triggering
    ~Bomb(void) {} //bomb destructor
};

class Painter :public Bonus //child class of bonus, which repaints gems in color of activation gem
{
private:
    unsigned paintedNumber = 2; //number of gems painted by this bonus
    unsigned paintedRadius = 3; //position of gems, which can be painted by this bonus

public:
    Painter(unsigned newX, unsigned newY) :Bonus(newX, newY, 1) {} //painter constructor with sending position of bonus and type of it
    unsigned Trigger(std::shared_ptr<Field> field) override; //painter triggering
    ~Painter(void) {} //painter destructor
};
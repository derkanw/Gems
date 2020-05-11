#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "ClassField.h"
#include "Bonus.h"

class GameLoop //implements the entire gameplay class
{
private:
    unsigned userWindowHeight, userWindowWidth; //size of window
    unsigned fieldWindowHeight, fieldWindowWidth; //size of field with gems
    unsigned numberGemsInRow, numberGemsInColumn; //number of gems in row and column
    unsigned score; //gems destroyed counter
    float offsetHeight, offsetWidth; //substruction between size of user's window and field's size

    bool drop; //shows whether the fall of gems continues
    bool secondClick; //show whether the second gem selected 
    bool swap, firstswap; //shows whether the gems swapping

    unsigned gem1X, gem1Y, gem2X, gem2Y; //keeps coordinates of two gems

    std::shared_ptr <sf::RenderWindow> window; //pointer to the game window
    std::shared_ptr <Field> field; //pointer to the game field
    std::vector<std::shared_ptr<Bonus>> bonusesMatrix; //set of bonuses' pointers

public:
    GameLoop(void); //constructor
    ~GameLoop(void) {} //destructor

    void FieldOffset(void); //defines offsets of gem to move field with gems around the window
    void Start(void); //all the gameplay
    void SpawnBonus(void); //spawn bonus (bomb or painter) with chance 5% in radius of 3 gems around the matching gem

    void BonusTrigger(void); //bonus triggering
    void GemsDeletion(void); //delition gems' combinations
    void GemsSwap(void); //changing position of two matching gems

    void DrawGameLoop(void); //drawing all figure on the field
    void CreateText(void); //showing score

    void Win(void); //if the player won
};
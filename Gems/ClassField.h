#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <memory>
#include "ClassGem.h"

class Field //Class that keeps gems in matrix
{
private:
    float height, width; //size of field with gems
    unsigned gemsInRow, gemsInColumn; //number of gems in row and column

    std::vector <std::vector <Gem>> gemsMatrix; //matrix of gems
    std::array <sf::Color, 6> colorsMatrix = { sf::Color::Blue, sf::Color::Green, sf::Color::Red, sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan }; /*
    matrix of gems' colors*/
    std::vector <std::array <unsigned, 2>> reiteration; //vector of gems' coordinate the same color
    std::vector <sf::Texture> textureMatrix; //keeping textures of bonuses

public:
    Field(float fieldWindowHeight, float fieldWindowWidth, unsigned numberGemsInRow, unsigned numberGemsInColumn); //field constructor
    ~Field(void) {} //field destructor

    void GenerateField(void); //filling the field
    void DrawField(std::shared_ptr <sf::RenderWindow> window, float offsetHeight, float offsetWidth); //drawing field with gems

    unsigned GetGemsInRow(void); //getting number of gems in field's row
    unsigned GetGemsInColumn(void); //getting number of gems in field's column
    float GetFieldHeight(void);  //getting height of field
    float GetFieldWidth(void); //getting width of field

    void CheckField(unsigned i, unsigned j); //find neighbours of a gem which have the same color
    bool NeighborIsGood(unsigned i, unsigned j, unsigned neighborI, unsigned neighborJ); //support function to check neighbors of gem
    bool AlreadyChoose(unsigned i, unsigned j, std::vector <std::array <unsigned, 2>> checkVector); /*
    doesn't allow adding an already checked element to the vector*/
    unsigned DeleteChoosedGems(std::vector <std::array <unsigned, 2>> forDeletion); //delete compination of gems which have the same color
    unsigned FindGemsReiteration(void); //àind and delete gems' reiteration

    bool GemsDrop(void); //upper gems drop for filling out the field
    void FieldRefilling(void); //refilling empty cells by new gems

    void SetHighlight(unsigned x, unsigned y, sf::Color newColor); //setting gem's highlighter
    void GemsSwap(unsigned x1, unsigned y1, unsigned x2, unsigned y2); //swapping two gems

    void SetNewGemsColor(std::vector <std::array <unsigned, 2>> paintedGems, unsigned i, unsigned j); /*
    change color of choosed gems according to matching gem's color*/

    sf::Texture* GetTexture(unsigned type); //getting texture matched with the type of bonus
    bool GemIsEmpty(unsigned i, unsigned j); //check gem's emptiness
    std::vector <std::array <unsigned, 2>> GetReiterationVector(void); //getting vector, which keeps gems' combination
};
#include "ClassGameLoop.h"

int main(void)
{
    srand((unsigned)time(0)); //generation of random gems' colors
    
    GameLoop Game;

    Game.FieldOffset();
    Game.Start();

    return 0;
}
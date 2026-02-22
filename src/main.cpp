#include "game.h"

int main()
{
    GameObj game;

    while (game.getWindow().isOpen())
    {
        game.update();
        game.render();
    }

    return 0;
}
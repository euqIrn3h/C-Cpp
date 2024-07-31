#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Game.hpp"


int main(int argc, void** argv[])
{
    Game game;

    while (!game.GetWindow()->IsDone())
    {
        game.HandleInput();
        game.Update();
        game.Render();
    }

    return 0;
}



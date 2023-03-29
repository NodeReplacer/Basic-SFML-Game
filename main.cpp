#include "Game.h"

int main()
{
    Player player;
    Game game;

    //Initialize a random seed using time.
    srand(static_cast<unsigned>(time(0)));

    //game.running() only returns a boolean: The result of window.isOpen
    while (game.running())
    {
        //Update
        game.update();
        //Render
        game.render();
    }


}
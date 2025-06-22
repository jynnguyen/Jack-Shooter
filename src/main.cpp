#include "main.hpp"
#include "Game.hpp"
 
int main()
{
    const string config = "config.txt";
    Game* game = new Game(config);
    game->run();
    delete game;
}
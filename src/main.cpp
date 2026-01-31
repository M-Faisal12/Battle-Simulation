#include <iostream>
using namespace std;
#include "../include/app/Game.h"

int main()
{
    Game game(10,10);
    game.initialize(1,0);
    game.run();
    game.shutdown();
    std::cout << "After issuing and processing orders:" << std::endl;
    game.run();
    return 0;
}

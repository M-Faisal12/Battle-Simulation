#include <iostream>
#include <vector>
using namespace std;
#include "../include/app/Game.h"
#include "../include/utils/Queue.h"
#include "../include/data/Map.h"
#include "../include/utils/BFS.h"
#include "../include/data/Unit.h"

int main()
{
    Game game(10,10);
    game.initialize(2);
    game.run();
    game.shutdown();
    return 0;
}

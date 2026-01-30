#ifndef GAME_H
#define GAME_H

#include "../data/Map.h"
#include "../data/Unit.h"

class Game {
    int width;
    int height;
    MAP::GRID* map;
    UnitFactory* units;
public:
    Game(int a,int b);
    ~Game();
    
    void initialize(int inf=0,int arc=0);
    void run();
    void shutdown();
    
private:
};

#endif // GAME_H

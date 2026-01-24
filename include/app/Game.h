#ifndef GAME_H
#define GAME_H

#include "../data/Map.h"
#include "../data/Unit.h"

class Game {
public:
    Game();
    ~Game();
    
    void initialize();
    void run();
    void shutdown();
    
private:
};

#endif // GAME_H

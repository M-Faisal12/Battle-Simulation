#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H
#include "../data/Unit.h"
#include "../data/Map.h"
#include "../utils/BFS.h"
#include <stack>
class MovementSystem {
    std::stack<int> movementStack;
    int* path;
public:
    MovementSystem();
    ~MovementSystem();
    void ProcessMovement(int unitID, int targetX, int targetY,UnitFactory* units, MAP::GRID* map);
    void Simulate(MAP::GRID* map);
private:
};

#endif // MOVEMENT_SYSTEM_H

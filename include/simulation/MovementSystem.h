#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H
#include "../data/Unit.h"
#include "../data/Map.h"
class MovementSystem {
public:
    MovementSystem();
    ~MovementSystem();
    void ProcessMovement(int unitID, int targetX, int targetY,UnitFactory* units, MAP::GRID* map);
private:
};

#endif // MOVEMENT_SYSTEM_H

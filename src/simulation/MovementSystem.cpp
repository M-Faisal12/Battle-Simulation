#include "../../include/simulation/MovementSystem.h"

MovementSystem::MovementSystem()
{
    path = nullptr;
}

MovementSystem::~MovementSystem()
{
    if (path != nullptr)
        delete[] path;
}
void MovementSystem::ProcessMovement(int unitID, int targetX, int targetY, UnitFactory *units, MAP::GRID *map)
{
    path = BFS(map->getTiles(), units->GetUnit(unitID)->X_Cord, units->GetUnit(unitID)->Y_Cord, targetX, targetY);
    if (!path)
    {
        // No path found
        return;
    }
    map->getTiles()[units->GetUnit(unitID)->Y_Cord * map->getWidth() + units->GetUnit(unitID)->X_Cord].symbol = '.';
    map->getTiles()[units->GetUnit(unitID)->Y_Cord * map->getWidth() + units->GetUnit(unitID)->X_Cord].PlayerId = -1;

    units->GetUnit(unitID)->X_Cord = targetX;
    units->GetUnit(unitID)->Y_Cord = targetY;
    map->getTiles()[units->GetUnit(unitID)->Y_Cord * map->getWidth() + units->GetUnit(unitID)->X_Cord].symbol = 'U';
    // map->getTiles()[units->GetUnit(unitID)->Y_Cord*map->getWidth()+units->GetUnit(unitID)->X_Cord].PlayerId=unitID;
    int a = path[targetY * map->getWidth() + targetX];
    while (a != -1)
    {
        movementStack.push(a);
        a = path[a];
    }
    delete[] path;
}
void MovementSystem::Simulate(MAP::GRID* map)
{
  map->getTiles()[movementStack.top()].symbol = 'P';
    movementStack.pop();
}
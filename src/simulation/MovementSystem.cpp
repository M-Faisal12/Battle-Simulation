#include "../../include/simulation/MovementSystem.h"

MovementSystem::MovementSystem() {
}

MovementSystem::~MovementSystem() {
}
void MovementSystem::ProcessMovement(int unitID, int targetX, int targetY,UnitFactory* units, MAP::GRID* map) {
map->getTiles()[units->GetUnit(unitID)->Y_Cord*map->getWidth()+units->GetUnit(unitID)->X_Cord].symbol='.';
map->getTiles()[units->GetUnit(unitID)->Y_Cord*map->getWidth()+units->GetUnit(unitID)->X_Cord].PlayerId=-1;
units->GetUnit(unitID)->X_Cord=targetX;
units->GetUnit(unitID)->Y_Cord=targetY;
map->getTiles()[units->GetUnit(unitID)->Y_Cord*map->getWidth()+units->GetUnit(unitID)->X_Cord].symbol='U';
map->getTiles()[units->GetUnit(unitID)->Y_Cord*map->getWidth()+units->GetUnit(unitID)->X_Cord].PlayerId=unitID;
}
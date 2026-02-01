#ifndef SIMULATION_H
#define SIMULATION_H
#include "OrderSystem.h"
#include "../data/Map.h"
class Simulation {
    OrderSystem* orderSystem;
public:
    Simulation();
    ~Simulation();
    OrderSystem* getOrderSystem() { return orderSystem; }
    
    void update(float deltaTime);
    void processRound(MAP::GRID* map);
    
private:
};

#endif // SIMULATION_H

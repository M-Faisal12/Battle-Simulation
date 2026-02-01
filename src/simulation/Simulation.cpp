#include "../../include/simulation/Simulation.h"

Simulation::Simulation() {
    orderSystem = new OrderSystem();
}

Simulation::~Simulation() {
    delete orderSystem;
}

void Simulation::update(float deltaTime) {
}

void Simulation::processRound(MAP::GRID* map) {
    orderSystem->Simulate(map);
}

#ifndef SIMULATION_H
#define SIMULATION_H

class Simulation {
public:
    Simulation();
    ~Simulation();
    
    void update(float deltaTime);
    void processRound();
    
private:
};

#endif // SIMULATION_H

#ifndef STATS_H
#define STATS_H

struct Stats {
    int health;
    int maxHealth;
    int strength;
    int defense;
    int speed;
    int accuracy;
    int evasion;
    
    Stats(int hp = 100, int str = 10, int def = 5, int spd = 5, int acc = 80, int eva = 10)
        : health(hp), maxHealth(hp), strength(str), defense(def), speed(spd), 
          accuracy(acc), evasion(eva) {}
};

#endif // STATS_H

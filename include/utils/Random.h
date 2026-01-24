#ifndef RANDOM_H
#define RANDOM_H

class Random {
public:
    Random();
    ~Random();
    
    int getInt(int min, int max);
    float getFloat(float min, float max);
    bool getChance(int percentage);
};

#endif // RANDOM_H

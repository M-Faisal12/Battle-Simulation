#ifndef MORALE_H
#define MORALE_H

enum class MoraleState {
    EXCELLENT,
    GOOD,
    NORMAL,
    POOR,
    BROKEN
};

class Morale {
public:
    Morale();
    ~Morale();
    
    void setMorale(int value);
    void adjustMorale(int delta);
    int getMorale() const { return morale; }
    MoraleState getState() const { return state; }
    float getMoraleMultiplier() const;
    
private:
    int morale;
    MoraleState state;
    
    void updateState();
};

#endif // MORALE_H

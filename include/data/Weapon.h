#ifndef WEAPON_H
#define WEAPON_H

enum class WeaponType {
    SWORD,
    BOW,
    STAFF,
    SPEAR,
    AXE
};

class Weapon {
public:
    Weapon(WeaponType type = WeaponType::SWORD);
    ~Weapon();
    
    int getAttackPower() const { return attackPower; }
    int getRange() const { return range; }
    WeaponType getType() const { return type; }
    int getAccuracy() const { return accuracy; }
    
private:
    WeaponType type;
    int attackPower;
    int range;
    int accuracy;
};

#endif // WEAPON_H

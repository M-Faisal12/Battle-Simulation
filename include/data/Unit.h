#pragma once
#include "Accessories.h"
#include "../utils/AVL.h"
struct Unit
{
    int id;
    int X_Cord;
    int Y_Cord;
    const int Maximum_health = 100;
    int health;
    int attack;
    int defense;
    Weapon::Weapon *weapon;
    Armor::Armor *armor;
    Shield::Shield *shield;
    Unit(int a, int x, int y, Weapon::WeaponType wtype = Weapon::WeaponType::AXE,
         Armor::ArmorType atype = Armor::ArmorType::LIGHT,
         Shield::ShieldType stype = Shield::ShieldType::WOODEN);
};
class UnitFactory
{
    int nextId;
    AVL<int, Unit *> UnitPool;

public:
    UnitFactory() : nextId(1) {}
    int RegisterUnit(int x, int y, Weapon::WeaponType wtype,
                      Armor::ArmorType atype,
                      Shield::ShieldType stype);
    void DeregisterUnit(int id);
    Unit *GetUnit(int id);
};
#include "../../include/data/Unit.h"
Unit::Unit(int a, int x, int y, Weapon::WeaponType wtype,
           Armor::ArmorType atype,
           Shield::ShieldType stype)
{
    id = a;
    X_Cord = x;
    Y_Cord = y;
    health = Maximum_health;
    weapon = new Weapon::Weapon(wtype);
    armor = new Armor::Armor(atype);
    shield = new Shield::Shield(wtype == Weapon::WeaponType::BOW ? Shield::ShieldType::NONE : stype);
    // Calculate attack based on weight of armor and shield percentage
    attack = weapon->getAttackPower()-(weapon->getAttackPower()* (armor->getWeight()+shield->getWeight())/100);
    // Calculate defense
    defense = armor->getDefenseValue() + shield->getDefenseValue();
}
int UnitFactory::RegisterUnit(int x, int y, Weapon::WeaponType wtype,
                               Armor::ArmorType atype,
                               Shield::ShieldType stype)
{
    Unit *newUnit = new Unit(nextId, x, y, wtype, atype, stype);
    UnitPool.insert(nextId, newUnit);
    nextId++;
    return nextId - 1;
}
void UnitFactory::DeregisterUnit(int id)
{
    UnitPool.remove(id);
}
Unit *UnitFactory::GetUnit(int id)
{
    return UnitPool.find(id);
}
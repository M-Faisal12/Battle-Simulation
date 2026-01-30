#ifndef WEAPON_H
#define WEAPON_H

namespace Weapon
{
    enum class WeaponType
    {
        SWORD,
        BOW,
        SPEAR,
        AXE
    };

    class Weapon
    {
    public:
        Weapon(WeaponType type = WeaponType::AXE)
        {
            this->type = type;
            switch (type)
            {
            case WeaponType::SWORD:
                attackPower = 15;
                range = 3;
                break;
            case WeaponType::BOW:
                attackPower = 10;
                range = 5;
                break;
            case WeaponType::SPEAR:
                attackPower = 12;
                range = 2;
                break;
            case WeaponType::AXE:
                attackPower = 18;
                range = 1;
                break;
            }
        }
        ~Weapon();

        int getAttackPower() const { return attackPower; }
        int getRange() const { return range; }
        WeaponType getType() const { return type; }

    private:
        WeaponType type;
        int attackPower;
        int range;
    };
};
namespace Shield
{
    enum class ShieldType
    {
        NONE,
        WOODEN,
        IRON
    };
    class Shield
    {
        ShieldType type;
        int defenseValue;
        int durability;
        int weight;

    public:
        Shield(ShieldType type = ShieldType::NONE) : type(type)
        {
            switch (type)
            {
            case ShieldType::NONE:
                defenseValue = 0;
                durability = 0;
                weight = 0;
                break;
            case ShieldType::WOODEN:
                defenseValue = 5;
                durability = 100;
                weight = 5;
                break;
            case ShieldType::IRON:
                defenseValue = 10;
                durability = 80;
                weight = 10;
                break;
            }
        }
        ShieldType getType() const { return type; }
        int getDefenseValue() const { return defenseValue; }
        int getDurability() const { return durability; }
        int getWeight() const { return weight; }
    };
};

namespace Armor
{
    enum class ArmorType
    {
        LIGHT,
        HEAVY
    };
    class Armor
    {
        ArmorType type;
        int defenseValue;
        int weight;
        int durability;

    public:
        Armor(ArmorType type = ArmorType::LIGHT) : type(type)
        {
            switch (type)
            {
            case ArmorType::LIGHT:
                defenseValue = 5;
                weight = 5;
                durability = 100;
                break;
            case ArmorType::HEAVY:
                defenseValue = 15;
                weight = 15;
                durability = 60;
                break;
            }
        }
        ArmorType getType() const { return type; }
        int getDefenseValue() const { return defenseValue; }
        int getWeight() const { return weight; }
        int getDurability() const { return durability; }
    };
};
#endif // WEAPON_H

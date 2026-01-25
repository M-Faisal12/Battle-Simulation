#include "../../include/app/Game.h"

Game::Game(int a,int b) : width(a), height(b) {
    map = new MAP::GRID(width, height);
    map->BuildMAP();
    units = new UnitFactory();
}

Game::~Game() {
    delete map;
    delete units;
}

void Game::initialize(int players) {
    // Initialize game state with the specified number of players
    map->getTiles()[0].symbol = 'P';
    map->getTiles()[0].PlayerId=units->RegisterUnit(0, 0, Weapon::WeaponType::SWORD, Armor::ArmorType::LIGHT, Shield::ShieldType::WOODEN);
}

void Game::run() {
    for(int i=0;i<map->getWidth();i++)  
        {
            for(int j=0;j<map->getHeight();j++)
            {
                std::cout<<map->getTiles()[j*map->getWidth()+i].symbol<<" ";
            }
            std::cout<<std::endl;
        }
}

void Game::shutdown() {
}

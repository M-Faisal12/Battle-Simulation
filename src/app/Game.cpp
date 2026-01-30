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

void Game::initialize(int inf) {
    // Initialize game state with the specified number of players
    int xi=0;        //Starting x position for infantry
    int xa=width/2; //Starting x position for archers
    int yi=(inf/(width/2));
    if(yi<0) yi=0;
    for(int i=0;i<inf;i++)
    {
        int a=units->RegisterUnit(xi, yi, Weapon::WeaponType::SWORD, Armor::ArmorType::LIGHT, Shield::ShieldType::WOODEN);
        map->getTiles()[xi*width+yi].symbol='I';
        map->getTiles()[xi*width+yi].PlayerId=a;
        xi++;
        if(xi>=width/2)
        {
            xi=0;
            yi--;
        }
    }
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

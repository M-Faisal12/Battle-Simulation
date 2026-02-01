#include "../../include/app/Game.h"

Game::Game(int a,int b) : width(a), height(b) {
    map = new MAP::GRID(width, height);
    map->BuildMAP();
    units = new UnitFactory();
    simulation = new Simulation();
}

Game::~Game() {
    delete map;
    delete units;
    delete simulation;
}

void Game::initialize(int inf,int arc) {
    // Initialize game state with the specified number of players
    int xi=0;        //Starting x position for infantry
    int xa=width/2; //Starting x position for archers
    int yi=(inf/(width/2))-(inf%(width/2)==0?1:0); //Starting y position for infantry
    if(yi<0) yi=0;
    int ya=(arc/(width/2))-(arc%(width/2)==0?1:0); //Starting y position for archers
    if(ya<0) ya=0;
    for(int i=0;i<inf;i++)
    {
        int a=units->RegisterUnit(xi, yi, Weapon::WeaponType::SWORD, Armor::ArmorType::LIGHT, Shield::ShieldType::WOODEN);
        map->getTiles()[yi*width+xi].symbol='I';
        map->getTiles()[yi*width+xi].PlayerId=a;
        xi++;
        if(xi>=width/2)
        {
            xi=0;
            yi--;
        }
    }
    for(int i=0;i<arc;i++)
    {
        int a=units->RegisterUnit(xa, ya, Weapon::WeaponType::BOW, Armor::ArmorType::LIGHT, Shield::ShieldType::NONE);
        map->getTiles()[ya*width+xa].symbol='A';
        map->getTiles()[ya*width+xa].PlayerId=a;
        xa++;
        if(xa>=width)
        {
            xa=width/2;
            ya--;
        }
    }
}

void Game::run() {
    for(int i=0;i<map->getHeight();i++)  
        {
            for(int j=0;j<map->getWidth();j++)
            {
                std::cout<<map->getTiles()[i*map->getWidth()+j].symbol<<" ";
            }
            std::cout<<std::endl;
        }
}

void Game::shutdown() {
    Order order;
    order.type=OrderType::MOVE;
    int a,b;
    while(true)
    {
    std::cout<<"Enter target coordinates X Y for Unit ";
    std::cin>>a>>b;
    if(map->getTiles()[b*map->getWidth()+a].PlayerId!=-1)break;
    }
    order.unitID=map->getTiles()[b*map->getWidth()+a].PlayerId;
    std::cout<<"Enter target coordinates X Y to move to: ";
    std::cin>>order.targetX>>order.targetY;
   simulation->getOrderSystem()->issueOrder(order);
   simulation->getOrderSystem()->processOrders(units, map);
   std::cout<<std::endl;
   simulation->processRound(map);
   run();
   std::cout<<std::endl;
   simulation->processRound(map);
   run();
   std::cout<<std::endl;
   simulation->processRound(map);
   run();
   std::cout<<std::endl;
   simulation->processRound(map);
   run();
   simulation->processRound(map);

}

#ifndef ORDER_SYSTEM_H
#define ORDER_SYSTEM_H

#include "../utils/Queue.h"
#include "../data/Unit.h"
#include "../data/Map.h"
#include "MovementSystem.h"
#include "CombatSystem.h"

enum class OrderType {
    MOVE,
    ATTACK,
    DEFEND,
    HOLD
};

struct Order {
    OrderType type;
    int targetX;
    int targetY;
    int unitID;
};

class OrderSystem {
    MovementSystem movementSystem;
public:
    OrderSystem();
    ~OrderSystem();
    
    void issueOrder(const Order& order);
    void processOrders(UnitFactory* units, MAP::GRID* map);
    Order getNextOrder();
    bool hasOrders() const;
    
private:
    Queue<Order>* orderQueue;
};

#endif // ORDER_SYSTEM_H

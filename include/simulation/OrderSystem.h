#ifndef ORDER_SYSTEM_H
#define ORDER_SYSTEM_H

#include <queue>

enum class OrderType {
    MOVE,
    ATTACK,
    DEFEND,
    RETREAT,
    HOLD
};

struct Order {
    OrderType type;
    int targetX;
    int targetY;
    int unitID;
};

class OrderSystem {
public:
    OrderSystem();
    ~OrderSystem();
    
    void issueOrder(const Order& order);
    void processOrders();
    Order getNextOrder();
    bool hasOrders() const;
    
private:
    std::queue<Order> orderQueue;
};

#endif // ORDER_SYSTEM_H

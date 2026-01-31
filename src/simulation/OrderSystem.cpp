#include "../../include/simulation/OrderSystem.h"
#include <iostream>
OrderSystem::OrderSystem() {
    // Constructor implementation 
    orderQueue = new Queue<Order>();
}
OrderSystem::~OrderSystem() {
    // Destructor implementation 
    delete orderQueue;
}
void OrderSystem::issueOrder(const Order& order) {
    orderQueue->enqueue(order);
    std::cout << "Order issued: Unit " << order.unitID << " to ";
    std::cout << (order.type == OrderType::MOVE ? "MOVE" :
                  order.type == OrderType::ATTACK ? "ATTACK" :
                  order.type == OrderType::DEFEND ? "DEFEND" : "HOLD");
}
void OrderSystem::processOrders(UnitFactory* units, MAP::GRID* map) {
        movementSystem.ProcessMovement(getNextOrder().unitID, getNextOrder().targetX, getNextOrder().targetY,units,map);
}
Order OrderSystem::getNextOrder() {
    return orderQueue->peek();
}
bool OrderSystem::hasOrders() const {
    if(orderQueue->isEmpty()){
        return false;
    }
    return true;
}

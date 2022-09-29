#include "Orders.h"
#include <iostream>

using std::cout;
using std::endl;

OrdersList::OrdersList() {
}

void OrdersList::addOrder(Order* order) {
    ordersList.push_back(order);

}

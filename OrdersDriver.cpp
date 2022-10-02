#include "OrdersDriver.h"
#include "Orders.h"
#include <iostream>

using std::cout;
using std::endl;

int testOrdersLists(){
    Deploy dep1;
    Deploy dep2(12, "Canada");
    Deploy dep3(10, "Russia");
    Deploy dep4(30, "USA");

    OrdersList ordersList;

    ordersList.addOrder(&dep1);
    ordersList.addOrder(&dep2);
    ordersList.addOrder(&dep3);
    ordersList.addOrder(&dep4);

    ordersList.moveOrderDown(1);
    ordersList.moveOrderDown(0);
    ordersList.moveOrderDown(100);
    ordersList.moveOrderDown(ordersList.getSize());
    ordersList.moveOrderUp(0);
    ordersList.moveOrderUp(4);
    ordersList.moveOrderUp(100);

    cout << ordersList << endl;

    return 0;
}
#include "Orders.h"
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

// -------------- ORDERS LIST --------------
/**
 * Default Constructor
 */
OrdersList::OrdersList()
{
}

/**
 * Copy constructor
 * @param o OrdersList to be copied
 */
 OrdersList::OrdersList(const OrdersList &o)
 {
     this -> ordersList = o.ordersList;
 }

 /**
  * Function to add an order to the orders list
  * @param order order to be added
  */
void OrdersList::addOrder(Order* order)
{
    this -> ordersList.push_back(order);
}

int OrdersList::getSize()
{
    return this -> ordersList.size();
}

Order* OrdersList::getOrder(int index)
{
    return this -> ordersList[index - 1];
}

void OrdersList::removeOrder(int index)
{
    int size = this -> getSize();

    if(size == 0) {
        cout << "Orders list is empty. Impossible to remove order !" << endl;
    } else if(index  < 1 || index > size) {
        cout << "Index out of bound !";
    } else {
        delete this->ordersList[index - 1];
        this->ordersList.erase(this->ordersList.begin() + index - 1);
    }
}

void OrdersList::moveOrderUp(int index)
{
    int size = this -> getSize();

    if(size == 0 || size == 1) {
        cout << "Moving orders within the orders list is not possible at the moment" << endl;
    } else if (index == 1) {
        cout << "Order already on top of list." << endl;
    } else if (index < 1 || index > size) {
        cout << "Index out of bound !" << endl;
    } else {
        Order* temp = this -> ordersList[index - 1];
        this -> ordersList[index - 1] = this -> ordersList[index - 2];
        this -> ordersList[index - 2] = temp;
    }
}

void OrdersList::moveOrderDown(int index)
{
    int size = this -> getSize();

    if(size == 0 || size == 1) {
        cout << "Moving orders within the orders list is not possible at the moment" << endl;
    } else if (index == size) {
        cout << "Order already bottom of the list !" << endl;
    } else if (index < 1 || index > size) {
        cout << "Index out of bound !" << endl;
    } else {
        Order* temp = this -> ordersList[index - 1];
        this -> ordersList[index - 1] = this -> ordersList[index];
        this -> ordersList[index] = temp;
    }
}

ostream& OrdersList::printList(ostream& output)
{
    output << "Orders List: " << endl;
    for (Order* order: this->ordersList) {
        output << " - ";
        output << *order << endl;
    }
    return output;
}

ostream& operator << (ostream& output, OrdersList& o)
{
    return o.printList(output);
}

OrdersList::~OrdersList()
{
    vector<Order*>().swap(this->ordersList);
};


// -------------- ORDER --------------


/**
 * Stream insertion operator is overloaded for the Order
 * abstract class so polymorphism can be used to display
 * information of different type of order.
 * @param output
 * @param o
 * @return
 */
ostream& operator << (ostream& output, Order& o)
{
    return o.printOrder(output);
}

// -------------- DEPLOY ORDER --------------

Deploy::Deploy()
{
    this -> numOfArmies = 0;
    this -> targetTerritory = "None";
}

Deploy::Deploy(int numOfArmies, string targetTerritory)
{
    this->numOfArmies = numOfArmies;
    this->targetTerritory = targetTerritory;
}


/**
 * Copy constructor
 * @param d
 */
Deploy::Deploy(const Deploy& d)
{
    this->numOfArmies = d.numOfArmies;
    this->targetTerritory = d.targetTerritory;
}

/**
 * Destructor
 */

ostream& Deploy::printOrder(ostream &output) const
{
    output << "Deploying " << this->numOfArmies << " units to ";
    output << this->targetTerritory << " territory." << endl;
    return output;
}

void Deploy::execute() const
{
    cout << "Order being executed !" << endl;
    cout << this;
}

bool Deploy::validate() const
{
    cout << "Validation in progress ... " << endl;
    return true;
}





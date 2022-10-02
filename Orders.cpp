#include "Orders.h"
#include <iostream>
#include <utility>

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
    ordersList.push_back(order);
}

int OrdersList::getSize()
{
    return ordersList.size();
}

Order* OrdersList::getOrder(int index)
{
    return ordersList[index - 1];
}

void OrdersList::removeOrder(int index)
{
    int size = this -> getSize();

    if(size == 0) {
        cout << "Orders list is empty. Impossible to remove order !" << endl;
    } else if(index  < 1 || index > size) {
        cout << "Index out of bound !";
    } else {
        delete ordersList[index - 1];
        ordersList.erase(ordersList.begin() + index - 1);
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
        Order* temp = ordersList[index - 1];
        ordersList[index - 1] = ordersList[index - 2];
        ordersList[index - 2] = temp;
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
        Order* temp = ordersList[index - 1];
        ordersList[index - 1] = ordersList[index];
        ordersList[index] = temp;
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
 * information of different type of orders.
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



// -------------- ADVANCE ORDER --------------

Advance::Advance()
{
    this -> numOfArmies = 0;
    this -> sourceTerritory = "Source";
    this -> targetTerritory = "Target";
}

Advance::Advance(int numOfArmies, string sourceTerritory, string targetTerritory)
{
    this->numOfArmies = numOfArmies;
    this->sourceTerritory = sourceTerritory;
    this->targetTerritory = targetTerritory;
}


/**
 * Copy constructor
 * @param a
 */
Advance::Advance(const Advance& a)
{
    this->numOfArmies = a.numOfArmies;
    this->sourceTerritory = a.sourceTerritory;
    this->targetTerritory = a.targetTerritory;
}

ostream& Advance::printOrder(ostream &output) const
{
    output << "Advancing " << this->numOfArmies << " units from ";
    output << this->sourceTerritory << " territory " << " to ";
    output << this->targetTerritory << " territory." << endl;
    return output;
}

void Advance::execute() const
{
    cout << "Order being executed !" << endl;
    cout << this;
}

bool Advance::validate() const
{
    cout << "Validation in progress ... " << endl;
    return true;
}

// -------------- BOMB ORDER --------------

Bomb::Bomb()
{
    this -> targetTerritory = "Target";
}

Bomb::Bomb(string targetTerritory)
{
    this->targetTerritory = targetTerritory;
}


/**
 * Copy constructor
 * @param b
 */
Bomb::Bomb(const Bomb& b)
{
    this->targetTerritory = b.targetTerritory;
}

ostream& Bomb::printOrder(ostream &output) const
{
    output << "Bombing " << this->targetTerritory << " territory.";
    output << endl;
    return output;
}

void Bomb::execute() const
{
    cout << "Order being executed !" << endl;
    cout << this;
}

bool Bomb::validate() const
{
    cout << "Validation in progress ... " << endl;
    return true;
}

// -------------- BLOCKADE ORDER --------------

Blockade::Blockade()
{
    this -> targetTerritory = "Target";
}

Blockade::Blockade(string targetTerritory)
{
    this->targetTerritory = targetTerritory;
}


/**
 * Copy constructor
 * @param b
 */
Blockade::Blockade(const Blockade& b)
{
    this->targetTerritory = b.targetTerritory;
}

ostream& Blockade::printOrder(ostream &output) const
{
    output << "Blockade on " << this->targetTerritory << " territory.";
    output << endl;
    return output;
}

void Blockade::execute() const
{
    cout << "Order being executed !" << endl;
    cout << this;
}

bool Blockade::validate() const
{
    cout << "Validation in progress ... " << endl;
    return true;
}

// -------------- AIRLIFT ORDER --------------

Airlift::Airlift()
{
    this -> numOfArmies = 0;
    this -> sourceTerritory = "Source";
    this -> targetTerritory = "Target";
}

Airlift::Airlift(int numOfArmies, string sourceTerritory, string targetTerritory)
{
    this->numOfArmies = numOfArmies;
    this->sourceTerritory = sourceTerritory;
    this->targetTerritory = targetTerritory;
}


/**
 * Copy constructor
 * @param a
 */
Airlift::Airlift(const Airlift& a)
{
    this->numOfArmies = a.numOfArmies;
    this->sourceTerritory = a.sourceTerritory;
    this->targetTerritory = a.targetTerritory;
}

ostream& Airlift::printOrder(ostream &output) const
{
    output << "Airlift " << this->numOfArmies << " units from ";
    output << this->sourceTerritory << " territory " << " to ";
    output << this->targetTerritory << " territory." << endl;
    return output;
}

void Airlift::execute() const
{
    cout << "Order being executed !" << endl;
    cout << this;
}

bool Airlift::validate() const
{
    cout << "Validation in progress ... " << endl;
    return true;
}

// -------------- NEGOTIATE ORDER --------------

Negotiate::Negotiate()
{
    this -> targetPlayer = "Target Player";
}

Negotiate::Negotiate(string targetPlayer)
{
    this->targetPlayer = targetPlayer;
}


/**
 * Copy constructor
 * @param n
 */
Negotiate::Negotiate(const Negotiate& n)
{
    this->targetPlayer = n.targetPlayer;
}

ostream& Negotiate::printOrder(ostream &output) const
{
    output << "Negotiation order used on player " << this->targetPlayer;
    output << endl;
    return output;
}

void Negotiate::execute() const
{
    cout << "Order being executed !" << endl;
    cout << this;
}

bool Negotiate::validate() const
{
    cout << "Validation in progress ... " << endl;
    return true;
}

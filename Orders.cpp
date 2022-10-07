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
    for (Order* order: ordersList) {
        output << " - ";
        output << *order << endl;
    }
    return output;
}

/**
 * Stream insertion operator overloaded for OrdersList.
 * @param output
 * @param o
 * @return
 */
ostream& operator << (ostream& output, OrdersList& o)
{
    return o.printList(output);
}

/**
 * Assignment operator overload if a reference to a list
 * is passed.
 * @param o
 * @return
 */
OrdersList& OrdersList::operator=(const OrdersList& o)
{
   if (this != &o) {
       for(Order* order: ordersList) {
           delete order; // Delete existing orders.
       }
       int size = o.ordersList.size();
       //Initialize vector with same size as assigned object.
       this->ordersList = vector<Order*>(size);
       for(int i = 0; i < size; i++) {
           ordersList[i] = o.ordersList[i]->copy();
       }
       return *this;
   }
   return *this;
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
    this -> targetTerritory = nullptr;
}

Deploy::Deploy(int numOfArmies, Territory* targetTerritory)
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
    if(!validate()) {
       cout << "Invalid Order !" << endl;
    } else {
        cout << "Order being executed !" << endl;
        printOrder(cout);
    }
}

bool Deploy::validate() const
{
    cout << "Validation in progress ... " << endl;
    return true;
}

/**
 * Used to make deep copies of Order objects.
 * @return
 */
Deploy* Deploy::copy() const
{
    return new Deploy(*this);
}

/**
 * Assignment operator overload for Deploy class.
 * @param d
 * @return
 */
Deploy& Deploy::operator=(const Deploy &d)
{
    if (this != &d) { //Checking for self assignment
        this->numOfArmies = d.numOfArmies;
        this->targetTerritory = d.targetTerritory;
    }
    return *this;
}

/**
 * Default Destructor (No inline definition allowed)
 */
Deploy::~Deploy()
{
}


// -------------- ADVANCE ORDER --------------

Advance::Advance()
{
    this -> numOfArmies = 0;
    this -> sourceTerritory = nullptr;
    this -> targetTerritory = nullptr;
}

Advance::Advance(int numOfArmies, Territory* sourceTerritory, Territory* targetTerritory)
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
    if(!validate()) {
        cout << "Invalid Order !" << endl;
    } else {
        cout << "Order being executed !" << endl;
        printOrder(cout);
    }
}

bool Advance::validate() const
{
    cout << "Validation in progress ... " << endl;
    return true;
}

/**
 * Used to make deep copies of Order objects.
 * @return Reference to a new cloned Order object.
 */
Advance* Advance::copy() const
{
    return new Advance(*this);
}

/**
 * Assignment operator overload for Advance class.
 * @param a
 * @return
 */
Advance& Advance::operator=(const Advance &a)
{
    if (this != &a) { //Checking for self assignment
        this->numOfArmies = a.numOfArmies;
        this->sourceTerritory = a.sourceTerritory;
        this->targetTerritory = a.targetTerritory;
    }
    return *this;
}

/**
 * Default Destructor (No inline definition allowed)
 */
Advance::~Advance()
{
}

// -------------- BOMB ORDER --------------

Bomb::Bomb()
{
    this -> targetTerritory = nullptr;
}

Bomb::Bomb(Territory* targetTerritory)
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
    if(!validate()) {
        cout << "Invalid Order !" << endl;
    } else {
        cout << "Order being executed !" << endl;
        printOrder(cout);
    }
}

bool Bomb::validate() const
{
    cout << "Validation in progress ... " << endl;
    return true;
}

/**
 * Used to make deep copies of Order objects.
 * @return Reference to a new cloned Order object.
 */
Bomb* Bomb::copy() const
{
    return new Bomb(*this);
}

/**
 * Assignment operator overload for Bomb class.
 * @param b
 * @return
 */
Bomb& Bomb::operator=(const Bomb &b)
{
    if (this != &b) { //Checking for self assignment
        this->targetTerritory = b.targetTerritory;
    }
    return *this;
}

/**
 * Default Destructor (No inline definition allowed)
 */
Bomb::~Bomb()
{
}

// -------------- BLOCKADE ORDER --------------

Blockade::Blockade()
{
    this -> targetTerritory = nullptr;
}

Blockade::Blockade(Territory* targetTerritory)
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
    if(!validate()) {
        cout << "Invalid Order !" << endl;
    } else {
        cout << "Order being executed !" << endl;
        printOrder(cout);
    }
}

bool Blockade::validate() const
{
    cout << "Validation in progress ... " << endl;
    return true;
}

/**
 * Used to make deep copies of Order objects.
 * @return Reference to a new cloned Order object.
 */
Blockade* Blockade::copy() const
{
    return new Blockade(*this);
}

/**
 * Assignment operator overload for Blockade class.
 * @param b
 * @return
 */
Blockade& Blockade::operator=(const Blockade &b)
{
    if (this != &b) { //Checking for self assignment
        this->targetTerritory = b.targetTerritory;
    }
    return *this;
}

/**
 * Default Destructor (No inline definition allowed)
 */
Blockade::~Blockade()
{
}

// -------------- AIRLIFT ORDER --------------

Airlift::Airlift()
{
    this -> numOfArmies = 0;
    this -> sourceTerritory = nullptr;
    this -> targetTerritory = nullptr;
}

Airlift::Airlift(int numOfArmies, Territory* sourceTerritory, Territory* targetTerritory)
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
    if(!validate()) {
        cout << "Invalid Order !" << endl;
    } else {
        cout << "Order being executed !" << endl;
        printOrder(cout);
    }
}

bool Airlift::validate() const
{
    cout << "Validation in progress ... " << endl;
    return true;
}

/**
 * Used to make deep copies of Order objects.
 * @return Reference to a new cloned Order object.
 */
Airlift* Airlift::copy() const
{
    return new Airlift(*this);
}

/**
 * Assignment operator overload for Airlift class.
 * @param a
 * @return
 */
Airlift& Airlift::operator=(const Airlift &a)
{
    if (this != &a) { //Checking for self assignment
        this->numOfArmies = a.numOfArmies;
        this->sourceTerritory = a.sourceTerritory;
        this->targetTerritory = a.targetTerritory;
    }
    return *this;
}

/**
 * Default Destructor (No inline definition allowed)
 */
Airlift::~Airlift()
{
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
    if(!validate()) {
        cout << "Invalid Order !" << endl;
    } else {
        cout << "Order being executed !" << endl;
        printOrder(cout);
    }
}

bool Negotiate::validate() const
{
    cout << "Validation in progress ... " << endl;
    return true;
}

/**
 * Used to make deep copies of Order objects.
 * @return Reference to a new cloned Order object.
 */
Negotiate* Negotiate::copy() const
{
    return new Negotiate(*this);
}

/**
 * Assignment operator overload for Negotiate class.
 * @param n
 * @return
 */
Negotiate& Negotiate::operator=(const Negotiate& n)
{
    if (this != &n) {  //Checking for self assignment
        this->targetPlayer = n.targetPlayer;
    }

    return *this;
}

/**
 * Default Destructor (No inline definition allowed)
 */
Negotiate::~Negotiate()
{
}


#include "Orders.h"
#include <iostream>
#include <sstream>
#include <utility>
#include "Player.h"

using std::cout;
using std::endl;
using std::ostream;

// -------------- ORDERS LIST --------------
/**
 * Added neutral player for blockade order execute method
 */
static auto* neutralPlayer = new Player();

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
    notify(this);
}

int OrdersList::getSize()
{
    return ordersList.size();
}

Order* OrdersList::getOrder(int index)
{
    return ordersList[index - 1];
}


vector<Order*> OrdersList::getOrdersList() {
    return this->ordersList;
}

/**
 * Removes from the order list the order that
 * corresponds to the position given. Note that the
 * first element will be at position 1 not 0.
 * @param index
 */
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

/**
 * Move the orders specified up one position on the list.
 * Note that the first element will be at position 1 not 0.
 * @param index
 */
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

/**
 * Move the orders specified up one position on the list.
 * Note that the first element will be at position 1 not 0.
 * @param index
 */
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

string OrdersList::stringToLog() {
    Order* order = ordersList.back();
    return "Order added: " + order->stringToLog();
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

/**
 * Destructor for the OrdersList. First destroy the Orders pointed
 * to by the list then deallocate the vector's memory.
 */
OrdersList::~OrdersList()
{
    for(auto order: ordersList)
    {
        delete order;
        order = nullptr;
    }
    //Swapping content to a non-instantiated vector will deallocate its memory.
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
    this -> currentPlayer = nullptr;
}

Deploy::Deploy(Player* currentPlayer, int numOfArmies, Territory* targetTerritory)
{
    this->currentPlayer = currentPlayer;
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
    this->currentPlayer = d.currentPlayer;
}

ostream& Deploy::printOrder(ostream &output) const
{
    output << "Deploying " << this->numOfArmies << " units to ";
    output << this->targetTerritory->getName() << " territory." << endl;
    return output;
}

string Deploy::stringToLog() {
    return "Order Executed: Deploying " + std::to_string(this->numOfArmies) + " units to " +
           this->targetTerritory->getName() + " territory.\n";
}

/**
 * Verifies if order is valid then executes it.
 * (Execution yet to be implemented).
 */
void Deploy::execute()
{
    if(!validate()) {
       cout << "Invalid Order; Deploy not executed." << endl;
    } else {
        this->targetTerritory->setNumOfArmies(this->targetTerritory->getNumOfArmies() + this->numOfArmies);
        this->currentPlayer->setReinforcementPool(this->currentPlayer->getReinforcementPool() - this->numOfArmies);
        printOrder(cout);
        notify(this);
    }
}

/**
 * Verifies if given order is valid.
 * @return bool true if targetTerritory belongs to player
 */
bool Deploy::validate() const
{
    if (this->targetTerritory->getOwner() != this->currentPlayer) {
        cout << "Specified territory is not owned" << endl;
        return false;
    }
    cout << "Deploy order successfully verified. Ready for execution !" << endl;
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
        this->currentPlayer = d.currentPlayer;
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
    this->currentPlayer = nullptr;
}

Advance::Advance(Player* currentPlayer, int numOfArmies, Territory* sourceTerritory, Territory* targetTerritory)
{
    this->numOfArmies = numOfArmies;
    this->sourceTerritory = sourceTerritory;
    this->targetTerritory = targetTerritory;
    this->currentPlayer = currentPlayer;
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
    this->currentPlayer = a.currentPlayer;
}

ostream& Advance::printOrder(ostream &output) const
{
    output << "Advancing " << this->numOfArmies << " units from ";
    output << this->sourceTerritory->getName() << " territory to ";
    output << this->targetTerritory->getName() << " territory." << endl;
    return output;
}

string Advance::stringToLog() {
    return "Order Executed: Advancing " + std::to_string(this->numOfArmies) + " units from " +
    this->sourceTerritory->getName() + " territory to " + this->targetTerritory->getName() +
    " territory.\n";
}

/**
 * Simulates an attack by a certain number of army units
 * from a source territory to a target territory.
 */
void Advance::attackSimulation() const {
    sourceTerritory->setNumOfArmies(sourceTerritory->getNumOfArmies() - numOfArmies);
    srand((unsigned) time(0));
    int randomNumber;
    int attackersKilled = 0;
    int defendersKilled = 0;

    for(int i = 0; i < numOfArmies; i++) {
        if(defendersKilled < targetTerritory->getNumOfArmies()) {
            randomNumber = (rand() % 100) + 1;
            if(randomNumber <= 60) {
                defendersKilled++;
            }
        } else {
            break;
        }
    }

    for(int i = 0; i < targetTerritory->getNumOfArmies(); i++) {
       if(attackersKilled < numOfArmies) {
           randomNumber = (rand() % 100) + 1;
           if(randomNumber <= 70) {
               attackersKilled++;
           }
       } else {
           break;
       }
    }
    int remainingAttackers = numOfArmies - attackersKilled;
    int remainingDefenders = targetTerritory->getNumOfArmies() - defendersKilled;

    if(remainingDefenders == 0 && remainingAttackers > 0) {
        cout << "Territory conquered !" << endl;
        currentPlayer->addTerritory(targetTerritory);
        targetTerritory->setOwner(currentPlayer);
        targetTerritory->setNumOfArmies(remainingAttackers);
        cout << "Player is eligible to get a card (MAX 1 PER TURN)" << endl;
        currentPlayer->setEntitledToCard(true);
    } else {
        cout << "Territory successfully defended !" << endl;
        targetTerritory->setNumOfArmies(remainingDefenders);
        sourceTerritory->setNumOfArmies(sourceTerritory->getNumOfArmies() + remainingAttackers);
    }
}

/**
 * Verifies if order is valid then executes it.
 */
void Advance::execute()
{
   if(!validate()) {
<<<<<<< HEAD
       cout << "Invalid Order; Advance not executed." << endl;
   } else if(targetTerritory->getOwner()->getName() == sourceTerritory->getOwner()->getName()) {
=======
       cout << "Invalid Order !" << endl;
   } else if(targetTerritory->getOwner() == sourceTerritory->getOwner()) {
>>>>>>> 5a7f7ef474db2f4349209f38d49e9c380740995e
       sourceTerritory->setNumOfArmies(sourceTerritory->getNumOfArmies() - numOfArmies);
       targetTerritory->setNumOfArmies(targetTerritory->getNumOfArmies() + numOfArmies);
       printOrder(cout);
       notify(this);
   } else {
       printOrder(cout);
       attackSimulation();
       notify(this);
   }
}

/**
 * Verifies if source territory is owned by current player and if
 * targetTerritory is adjacent to sourceTerritory
 * @return true if conditions are met.
 */
bool Advance::validate() const
{
   if (this->sourceTerritory->getOwner() != this->currentPlayer) {
       cout << "Source territory is not owned" << endl;
       return false;
   } else if (!this->sourceTerritory->isAdjacentTerritory(targetTerritory)) {
       cout << "Source and target territory are not adjacent. Move is impossible !" << endl;
       return false;
   }else if(currentPlayer->isAlly(targetTerritory->getOwner())){
       cout << "Target territory owner is an ally; cant attack!" << endl;
       return false;
   }
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
        this->currentPlayer = a.currentPlayer;
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
    this -> currentPlayer = nullptr;
}

Bomb::Bomb(Player* currentPlayer, Territory* targetTerritory)
{
    this->targetTerritory = targetTerritory;
    this->currentPlayer = currentPlayer;
}


/**
 * Copy constructor
 * @param b
 */
Bomb::Bomb(const Bomb& b)
{
    this->targetTerritory = b.targetTerritory;
    this->currentPlayer = b.currentPlayer;
}

ostream& Bomb::printOrder(ostream &output) const
{
    output << "Bombing " << this->targetTerritory->getName() << " territory.";
    output << endl;
    return output;
}

string Bomb::stringToLog() {
    return "Order Executed: Bombing " + this->targetTerritory->getName() + " territory.\n";
}

/**
 * Verifies if order is valid then executes it.
 * (Execution yet to be implemented).
 */
void Bomb::execute()
{
    if(!validate()) {
        cout << "Invalid Order; Bomb not executed." << endl;
    } else {
        targetTerritory->setNumOfArmies(targetTerritory->getNumOfArmies() / 2);
        printOrder(cout);
        notify(this);
    }
}

/**
 * Verifies if given order is valid.
 * (Validation yet to be implemented).
 * @return
 */
bool Bomb::validate() const
{
    if( this->targetTerritory->getOwner() == this->currentPlayer){
        cout << "Target territory is owned by the player issuing the order" << endl;
        return false;
    }else if (!(this->currentPlayer->isAdjacentTerritory(targetTerritory))){
        cout << "Target territory is not adjacent to a territory owned by player issuing the order" <<endl;
        return false;
    }else if(currentPlayer->isAlly(targetTerritory->getOwner())){
        cout << "Target territory owner is an ally; cant attack!" << endl;
        return false;
    }
    cout << "Bomb order successfully verified. Ready for execution !" << endl;
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
    this -> currentPlayer = nullptr;
}

Blockade::Blockade(Player* currentPlayer, Territory* targetTerritory)
{
    this->targetTerritory = targetTerritory;
    this->currentPlayer = currentPlayer;
}


/**
 * Copy constructor
 * @param b
 */
Blockade::Blockade(const Blockade& b)
{
    this->targetTerritory = b.targetTerritory;
    this->currentPlayer = b.currentPlayer;
}

ostream& Blockade::printOrder(ostream &output) const
{
    output << "Blockade on " << this->targetTerritory->getName() << " territory.";
    output << endl;
    return output;
}

string Blockade::stringToLog() {
    return "Order Executed: Blockade on " + this->targetTerritory->getName() + " territory.\n";
}

/**
 * Verifies if order is valid then executes it.
 * (Execution yet to be implemented).
 */
void Blockade::execute()
{
    if(!validate()) {
        cout << "Invalid Order; Blockade not executed." << endl;
    } else {
        targetTerritory->setNumOfArmies(targetTerritory->getNumOfArmies() * 2);
        targetTerritory->setOwner(neutralPlayer);
        printOrder(cout);
        notify(this);
    }
}

/**
 * Verifies if given order is valid.
 * (Validation yet to be implemented).
 * @return
 */
bool Blockade::validate() const
{
    if(this->targetTerritory->getOwner() != this->currentPlayer){
        cout << "Target territory is not owned by the player issuing the order" << endl;
        return false;
    }
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
        this->currentPlayer = b.currentPlayer;
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
    this -> currentPlayer = nullptr;
}

Airlift::Airlift(Player* currentPlayer, int numOfArmies, Territory* sourceTerritory, Territory* targetTerritory)
{
    this->numOfArmies = numOfArmies;
    this->sourceTerritory = sourceTerritory;
    this->targetTerritory = targetTerritory;
    this->currentPlayer = currentPlayer;
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
    this->currentPlayer = a.currentPlayer;
}

ostream& Airlift::printOrder(ostream &output) const
{
    output << "Airlift " << this->numOfArmies << " units from ";
    output << this->sourceTerritory->getName() << " territory " << " to ";
    output << this->targetTerritory->getName() << " territory." << endl;
    return output;
}

string Airlift::stringToLog() {
    return "Order Executed: Airlift " + std::to_string(this->numOfArmies) + " units from " +
    this->sourceTerritory->getName() + " territory to " + this->targetTerritory->getName() +
    " territory.\n";
}

/**
 * Verifies if order is valid then executes it.
 * (Execution yet to be implemented).
 */
void Airlift::execute()
{
    if(!validate()) {
        cout << "Invalid Order; Airlift not executed." << endl;
    } else {
        sourceTerritory->setNumOfArmies(sourceTerritory->getNumOfArmies() - numOfArmies);
        targetTerritory->setNumOfArmies(targetTerritory->getNumOfArmies() + numOfArmies);
        printOrder(cout);
        notify(this);

    }
}

/**
 * Verifies if both target and source territories are
 * owned by the issuing player.
 * @return True if both target and source territory are owned by
 * the issuing player.
 */
bool Airlift::validate() const
{
    if (this->sourceTerritory->getOwner() != this->currentPlayer ||
    this->targetTerritory->getOwner() != this->currentPlayer) {
        cout << "Source and/or target territory are not owned" << endl;
        return false;
    }
    cout << "Airlift order successfully verified. Ready for execution !" << endl;
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
        this->currentPlayer = a.currentPlayer;
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
    this -> targetPlayer = nullptr;
}

Negotiate::Negotiate(Player* currentPlayer, Player* targetPlayer)
{
    this->targetPlayer = targetPlayer;
    this->currentPlayer = currentPlayer;
}


/**
 * Copy constructor
 * @param n
 */
Negotiate::Negotiate(const Negotiate& n)
{
    this->targetPlayer = n.targetPlayer;
    this->currentPlayer = n.currentPlayer;
}

ostream& Negotiate::printOrder(ostream &output) const
{
    output << "Negotiation order used on player " << this->targetPlayer->getName();
    output << endl;
    return output;
}

string Negotiate::stringToLog() {
    return "Order Executed: Negotiation order used on player " + this->targetPlayer->getName() + ".\n";
}

/**
 * Verifies if order is valid then executes it.
 * (Execution yet to be implemented).
 */
void Negotiate::execute()
{
    if(!validate()) {
        cout << "Invalid Order; Negotiate not executed." << endl;
    } else {
        this->currentPlayer->addAlly(targetPlayer);
        this->targetPlayer->addAlly(currentPlayer);
        printOrder(cout);
        notify(this);
    }
}

/**
 * Verifies if given order is valid.
 * (Validation yet to be implemented).
 * @return
 */
bool Negotiate::validate() const
{
    if(targetPlayer == currentPlayer){
        cout << "The target player must be different than the player issuing the order" <<endl;
        return false;
    }
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
        this->currentPlayer = n.currentPlayer;
    }

    return *this;
}

/**
 * Default Destructor (No inline definition allowed)
 */
Negotiate::~Negotiate()
{
}


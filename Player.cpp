#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

using namespace std;

/**
 * Overloading stream insertion operator
 * @param strm
 * @param p
 * @return
 */
ostream & operator<<(ostream &strm, const Player &p){
    return strm << "Player: " << p.name << " owns " << p.ownedTerritories.size() << " territories and has " << p.orderList->getSize() << " orders." << endl;
}


/**
 * Default constructor
 */
Player::Player(){
}

/**
 * Destructor
 */
Player::~Player() {
    delete hand;
    delete orderList;
    hand = nullptr;
    orderList = nullptr;
    vector<Territory*>().swap(this->ownedTerritories);
    vector<Player*>().swap(this->allyPlayerList);

}

Player::Player(string name, Hand* hand, OrdersList* ordersList, int reinforcementPool) {
    this->name = name;
    this->hand =hand;
    this->orderList = ordersList;
    this->reinforcementPool = reinforcementPool;
}

/**
 * Copy constructor (deep copy for hand and orderlist, but not territories)
 * @param p
 */
Player::Player(const Player &p){
    this->hand = new Hand(*(p.hand));
    this->orderList = new OrdersList(*(p.orderList));
    this->hand->setOwner(this);
    this->reinforcementPool = p.reinforcementPool;
    for(auto territory:p.ownedTerritories){
        ownedTerritories.push_back(territory);
    }
    for(auto player: p.allyPlayerList){
        allyPlayerList.push_back(player);
    }
}

/**
 * Overloading assignment operator
 * @param t
 * @return
 */
Player& Player::operator=(const Player &p) {
    this->hand = new Hand(*(p.hand));
    this->orderList = new OrdersList(*p.orderList);
    this->hand->setOwner(this);
    this->reinforcementPool = p.reinforcementPool;
    for(auto territory:p.ownedTerritories){
        ownedTerritories.push_back(territory);
    }
    for(auto player : p.allyPlayerList){
        allyPlayerList.push_back(player);
    }
    return *this;
}

vector<Territory *> Player::getTerritories() {
    return ownedTerritories;
}

void Player::setTerritories(vector<Territory *> territories) {
    ownedTerritories = territories;
}

Hand *Player::getHand() {
    return hand;
}

void Player::setHand(Hand *hand) {
    this->hand = hand;
}

string Player::getName() {
    return this->name;
}

OrdersList *Player::getOrdersList() {
    return this->orderList;
}

void Player::setOrdersList(OrdersList *ordersList) {
    this->orderList = ordersList;
}

int Player::getReinforcementPool() {
    return this->reinforcementPool;
}

void Player::setReinforcementPool(int reinforcementPool) {
    this->reinforcementPool = reinforcementPool;
}

/**
 * Add reinforcements to Player's current reinforcement pool
 * @param reinforcements Number of reinforcements to add
 */
void Player::addReinforcements(int reinforcements) {
    this->reinforcementPool += reinforcements;
}

/**
 * Add territory to Player's owned territories list, and make the Player the owner of that territory
 * @param t
 */
void Player::addTerritory(Territory* t){
    this->ownedTerritories.push_back(t);
    t->setOwner(this);
}

/**
 * Adds a player to the list of ally
 * @param p  Player to be added as an ally for this turn
 */
void Player::addAlly(Player* p) {
   allyPlayerList.push_back(p);
}

/**
 * Returns a random list of territories (for now)
 * @return
 */
vector<Territory*> Player::toAttack(){    //attack method

    vector<Territory*> attackTerritories;

    // Initialize random seed to ensure randomness
    srand(time(NULL));

    int numOfTerritories = (rand() % ownedTerritories.size()) + 1; // generate number from 1 to number of owned territories
    for(int i = 0; i < numOfTerritories; i++) {
        int randomIndex = rand() % (ownedTerritories.size()-1);
        attackTerritories.push_back(ownedTerritories.at(randomIndex));
    }
    return attackTerritories;

}

/**
 * Returns a random list of territories (for now)
 * @return
 */
vector<Territory*> Player::toDefend(){    //defend method

    vector<Territory*> defendTerritories;

    // Initialize random seed to ensure randomness
    srand(time(NULL));

    int numOfTerritories = (rand() % ownedTerritories.size()) + 1; // generate number from 1 to number of owned territories
    for(int i = 0; i < numOfTerritories; i++) {
        int randomIndex = rand() % (ownedTerritories.size()-1);
        defendTerritories.push_back(ownedTerritories.at(randomIndex));
    }
    return defendTerritories;
}

/**
 * Create an order, and add it to the player's OrderList
 * @param orderID
 */
void Player::issueOrder(){

    // Deploy orders
    while(true) {
        // HARDCODED ORDER FOR THE PURPOSE OF THIS ASSIGNMENT:
        // For now, deploy all troops to the first territory in toDefend.
        int numOfArmies = this->reinforcementPool;
        Territory* targetTerritory = this->toDefend().front();
        Deploy* deploy = new Deploy(this, numOfArmies, targetTerritory);
        orderList->addOrder(deploy);

        // Once the reinforcementPool is empty, we can proceed to other orders
        if (this->reinforcementPool == 0) {
            break;
        }
    }

    // Other orders
    bool done = false;
    while(!done) {
        // HARDCODED ORDERS FOR THE PURPOSE OF THIS ASSIGNMENT:
        // For now, just try to (1) advance half the available troops from the first territory in toDefend to the first
        // territory in toAttack, then (2) advance another half of the available troops from the first territory in
        // getTerritories to the first territory in toDefend, finally (3) play the first card in hand (if it exists)

        Advance* attackOrder = new Advance(this, this->reinforcementPool/2, this->toDefend().front(), this->toAttack().front());
        orderList->addOrder(attackOrder);

        Advance* defendOrder = new Advance(this, this->reinforcementPool/2, this->getTerritories().front(), this->toDefend().front());
        orderList->addOrder(defendOrder);

        // Play the card
        if (!this->hand->getHandList()->empty()) {
            this->hand->playCard(1);
        }

        // Player indicates that they are done issuing orders for this turn
        done = true;
    }

//    if(orderID == 0){
//        Deploy * deploy = new Deploy();
//        orderList->addOrder(deploy);
//    }
//    else if(orderID == 1){
//        Advance* advance = new Advance();
//        orderList->addOrder(advance);
//    }
//    else if(orderID == 2){
//        Bomb* bomb = new Bomb();
//        orderList->addOrder(bomb);
//    }
//    else if(orderID == 3){
//        Blockade* blockade = new Blockade();
//        orderList->addOrder(blockade);
//    }
//    else if(orderID == 4){
//        Airlift* airlift = new Airlift();
//        orderList->addOrder(airlift);
//    }
//    else if(orderID == 5){
//        Negotiate* negotiate = new Negotiate();
//        orderList->addOrder(negotiate);
//    }
//    else{
//        cout << "Invalid order" << endl;
//    }
}

/**
 * Validate if the targetTerritory is adjacent to one territory owned by the currentPlayer
 * @param targetTerritory
 * @return
 */
bool Player::isAdjacentTerritory(Territory* targetTerritory) {
    for(auto& territory : ownedTerritories){
        if(territory->isAdjacentTerritory(targetTerritory)){
            return true;
        }
    }
    return false;
}

vector<Player*> Player::getAllyPlayerList() {
    return this->allyPlayerList;
}

/**
 * Verifies if the target player is an ally.
 * @param targetPlayer
 * @return
 */
bool Player::isAlly(Player* targetPlayer) {
    for(auto player:allyPlayerList){
        if(targetPlayer->getName() == player->getName()){
            return true;
        }
    }
    return false;
}
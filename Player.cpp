#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

#include <algorithm>
using std::find;

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
    delete strategy;
    hand = nullptr;
    orderList = nullptr;
    vector<Territory*>().swap(this->ownedTerritories);
    vector<Player*>().swap(this->allyPlayerList);

}

Player::Player(string name, Hand* hand, OrdersList* ordersList, int reinforcementPool) {
    this->name = name;
    this->hand = hand;
    this->orderList = ordersList;
    this->reinforcementPool = reinforcementPool;
    this->entitledToCard = false;
    this->strategy = nullptr;
}

Player::Player(std::string name) {
    this->name = name;
    this->hand = new Hand();
    this->orderList = new OrdersList();
    this->entitledToCard = false;
    this->strategy = nullptr;
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
    for(auto player: p.opponentPlayerList){
        opponentPlayerList.push_back(player);
    }
    this->strategy = p.strategy;
    strategy->setPlayer(this);
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
    for(auto player : p.opponentPlayerList){
        opponentPlayerList.push_back(player);
    }
    this->strategy = p.strategy;
    strategy->setPlayer(this);
    return *this;
}

vector<Territory *> Player::getTerritories() {
    return ownedTerritories;
}

Hand *Player::getHand() {
    return hand;
}

string Player::getName() {
    return this->name;
}

OrdersList *Player::getOrdersList() {
    return this->orderList;
}

int Player::getReinforcementPool() {
    return this->reinforcementPool;
}

bool Player::getEntitledToCard() {
    return this->entitledToCard;
}

PlayerStrategy* Player::getPlayerStrategy() {
    return this->strategy;
}

vector<Player*> Player::getAllyPlayerList() {
    return this->allyPlayerList;
}

vector<Player*> Player::getOpponentPlayerList() {
    return this->opponentPlayerList;
}

void Player::setReinforcementPool(int reinforcementPool) {
    this->reinforcementPool = reinforcementPool;
}

void Player::setOrdersList(OrdersList *ordersList) {
    this->orderList = ordersList;
}

void Player::setTerritories(vector<Territory *> territories) {
    ownedTerritories = territories;
}

void Player::setEntitledToCard(bool entitledToCard) {
    this->entitledToCard = entitledToCard;
}

void Player::setHand(Hand *hand) {
    this->hand = hand;
}

void Player::setAllyPlayerList(vector<Player *> allyPlayerList) {
    this->allyPlayerList = allyPlayerList;
}

void Player::setOpponentPlayerList(vector<Player *> opponentPlayerList) {
    this->opponentPlayerList = opponentPlayerList;
}

void Player::setPlayerStrategy(PlayerStrategy *ps)
{
    if(strategy == nullptr) {
        this->strategy = ps;
    } else {
        delete strategy;
        this->strategy = ps;
    }
}

/**
 * Add reinforcements to Player's current reinforcement pool
 * @param reinforcements Number of reinforcements to add
 */
void Player::addReinforcements(int reinforcements) {
    this->reinforcementPool += reinforcements;
}

void Player::setName(std::string name) {
    this->name = name;
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
 * Remove territory from Player's owned territories list.
 * @param t
 */
void Player::removeTerritory(Territory *t) {
    for(int i=0; i < this->ownedTerritories.size(); i++) {
        if (this->ownedTerritories.at(i) == t) {
           this->ownedTerritories.erase(this->ownedTerritories.begin() + i);
        }
    }

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
    return strategy->toAttack();

}

/**
 * Returns a random list of territories (for now)
 * @return
 */
vector<Territory*> Player::toDefend(){    //defend method
    return strategy->toDefend();
}

/**
 * Create an order, and uses the player strategy's
 * issueOrder method to make the decision and
 * add the resulting order it to the player's OrderList
 * @param orderID
 */
bool Player::issueOrder(bool isDeployPhase){
    return strategy->issueOrder(isDeployPhase);
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

/**
 * Verifies if the target player is an ally.
 * @param targetPlayer
 * @return
 */
bool Player::isAlly(Player* targetPlayer) {
    for(auto player:allyPlayerList){
        if(targetPlayer == player) {
            return true;
        }
    }
    return false;
}
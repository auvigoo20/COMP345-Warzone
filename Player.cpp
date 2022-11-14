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
}

Player::Player(std::string name) {
    this->name = name;
    this->hand = new Hand();
    this->orderList = new OrdersList();
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

    // generate number from 1 to number of owned territories
    int numOfTerritories = (rand() % ownedTerritories.size()) + 1;

    // If we have more than 1 territory, randomly pick (numOfTerritories) territories from the owned lest to return.
    // Else just return the 1 territory we have.
    if (ownedTerritories.size() > 1) {
        for (int i = 0; i < numOfTerritories; i++) {
            int randomIndex = rand() % (ownedTerritories.size() - 1);
            attackTerritories.push_back(ownedTerritories.at(randomIndex));
        }
    } else {
        attackTerritories.push_back(ownedTerritories.at(0));
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

    // generate number from 1 to number of owned territories
    int numOfTerritories = (rand() % ownedTerritories.size()) + 1;

    // If we have more than 1 territory, randomly pick (numOfTerritories) territories from the owned lest to return.
    // Else just return the 1 territory we have.
    if (ownedTerritories.size() > 1) {
        for(int i = 0; i < numOfTerritories; i++) {
            int randomIndex = rand() % (ownedTerritories.size()-1);
            defendTerritories.push_back(ownedTerritories.at(randomIndex));
        }
    } else {
        defendTerritories.push_back(ownedTerritories.at(0));
    }
    return defendTerritories;
}

/**
 * Create an order, and add it to the player's OrderList
 * @param orderID
 */
void Player::issueOrder(){
    cout << "Issuing deploy orders for " << this->getName() << " (" << this->getReinforcementPool() << " available troops, " << this->getTerritories().size() << " available territories)" << endl;

    // Deploy orders
    int numDeployed = 0;
    while(true) {
        cout << "Issuing order " << this->getOrdersList()->getSize() << " (deploy) for " << this->getName()  << endl;

        int toDeployNow = 0;
        Deploy* deploy;


        // HARDCODED ORDER FOR THE PURPOSE OF THIS ASSIGNMENT:
        // For now, deploy a troop to each territory in toDefend.
        for (Territory* territory : this->toDefend()) {
            if (numDeployed < this->reinforcementPool) {
                deploy = new Deploy(this, 1, territory);
                toDeployNow = 1;
            }
        }

        // After clarifying with the prof, since we need to check anyways that we are deploying all the troops in the
        // pool, it is allowed to do the validation re: attempting to deploy more troops than you have here.
        // Note that the validation that we are deploying to our own territory is NOT happening here, this will be done
        // during the execute phase.
        //
        // Do not create the order if you would exceed number of troops in reinforcementPool
        if ((numDeployed + toDeployNow) > this->reinforcementPool) {
            cout << "Invalid Order !" << endl;
        } else {
            orderList->addOrder(deploy);
            numDeployed += toDeployNow;
            toDeployNow = 0;
        }

        // Once we have deployed all available troops, we can proceed to other orders
        if (numDeployed == this->reinforcementPool) {
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

        cout << "Issuing order " << this->getOrdersList()->getSize() << " (advance) for " << this->getName()  << endl;
        Advance* attackOrder = new Advance(this, this->reinforcementPool/2, this->toDefend().front(), this->toAttack().front());
        orderList->addOrder(attackOrder);

        cout << "Issuing order " << this->getOrdersList()->getSize() << " (advance) for " << this->getName()  << endl;
        Advance* defendOrder = new Advance(this, this->reinforcementPool/2, this->getTerritories().front(), this->toDefend().front());
        orderList->addOrder(defendOrder);

        // Play the card
        // FOR NOW the parameters for playing the card are hardcoded.
        //
        // What will need to remain when the parameters are freed is this:
        // - The card's type needs to be determined
        // - The parameters need to be set
        // - The card's play() method needs to be called (to create the order and add it to orderlist)
        // - The hand's playCard() method needs to be called (to remove card from hand and put it back)
        if (!this->hand->getHandList()->empty()) {
            Card* card = this->hand->getHandList()->front();
            AirliftCard* airliftCard = dynamic_cast<AirliftCard*>(card);
            BombCard* bombCard = dynamic_cast<BombCard*>(card);
            BlockadeCard* blockadeCard = dynamic_cast<BlockadeCard*>(card);
            DiplomacyCard* diplomacyCard = dynamic_cast<DiplomacyCard*>(card);

            if (airliftCard != nullptr) {
                cout << "Playing airlift card for " << this->getName()  << endl;
                // For now just airlift half the units from the last territory in toDefend to the first territory in toDefend
                Territory* targetTerritory = this->toDefend().front();
                Territory* sourceTerritory = this->toDefend().back();
                int numOfArmies = sourceTerritory->getNumOfArmies() / 2;
                airliftCard->play(this, numOfArmies, sourceTerritory, targetTerritory);
                this->hand->playCard(0);
            }
            else if (bombCard != nullptr) {
                cout << "Playing bomb card for " << this->getName()  << endl;
                // For now just bomb a random territory in toAttack
                Territory* targetTerritory = this->toAttack().front();
                bombCard->play(this, targetTerritory);
                this->hand->playCard(0);
            }
            else if (blockadeCard != nullptr) {
                cout << "Playing blockade card for " << this->getName()  << endl;
                // For now just blockade a random territory in toAttack
                Territory* targetTerritory = this->toAttack().front();
                blockadeCard->play(this, targetTerritory);
                this->hand->playCard(0);
            }
            else if (diplomacyCard != nullptr) {
                cout << "Playing diplomacy card for " << this->getName()  << endl;
                // For now just ally with a random targetPlayer
                Player* targetPlayer = this->opponentPlayerList.front();
                diplomacyCard->play(this, targetPlayer);
                this->hand->playCard(0);
            }
        }

        // Player indicates that they are done issuing orders for this turn
        done = true;
    }
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
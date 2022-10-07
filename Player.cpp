#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

using namespace std;

//Default constructor
Player::Player(){
}

Player::Player(const Player &p){    //Copy constructor
    // TODO MAKE PROPER COPY CONSTRUCTOR
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

OrdersList *Player::getOrdersList() {
    return orderList;
}

void Player::setOrdersList(OrdersList *ordersList) {
    this->orderList = ordersList;
}

void Player::addTerritory(Territory* t){
    this->ownedTerritories.push_back(t);
    t->setOwner(this);
}

vector<Territory*> Player::toAttack(){    //attack method

    vector<Territory*> listToReturn;
    int numOfTerritories = rand() % ownedTerritories.size() - 1;
    for(int i = 0; i < numOfTerritories; i++) {
        int randomIndex = rand() % ownedTerritories.size() - 1;
        listToReturn.push_back(ownedTerritories.at(randomIndex));
    }
    return listToReturn;

}


vector<Territory*> Player::toDefend(){    //defend method
    vector<Territory*> listToReturn;
    int numOfTerritories = rand() % ownedTerritories.size() - 1;
    for(int i = 0; i < numOfTerritories; i++) {
        int randomIndex = rand() % ownedTerritories.size() - 1;
        listToReturn.push_back(ownedTerritories.at(randomIndex));
    }
    return listToReturn;
}

void Player::issueOrder(){

    int randomOrder = rand() % 5;

    if(randomOrder == 0){
        Deploy * deploy = new Deploy();
        orderList->addOrder(deploy);
    }
    else if(randomOrder == 1){
        Advance* advance = new Advance();
        orderList->addOrder(advance);
    }
    else if(randomOrder == 2){
        Bomb* bomb = new Bomb();
        orderList->addOrder(bomb);
    }
    else if(randomOrder == 3){
        Blockade* blockade = new Blockade();
        orderList->addOrder(blockade);
    }
    else if(randomOrder == 4){
        Airlift* airlift = new Airlift();
        orderList->addOrder(airlift);
    }
    else if(randomOrder == 5){
        Negotiate* negotiate = new Negotiate();
        orderList->addOrder(negotiate);
    }


}
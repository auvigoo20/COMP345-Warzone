#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

using namespace std;

Player::Player(){   //Default constructor
    string name;
    vector<Territory*> territory;
    vector<Hand*> handList;
    vector<Order*> orderList;
}

Player::Player(string name, vector<Territory*> territory, vector<Hand*> handList,vector<Order*> orderList){   //Constructor
    this->name = name;
    this->territoryList = territory;
    this->handCard = handCard;
    this->orderList = orderList;
}

Player::Player(const Player &p){    //Copy constructor
    this->name = p.name;
    this->territoryList = p.territoryList;
    this->handCard = p.handCard;
    this->orderList = p.orderList;
}

void Player::toAttack(){    //attack method
    cout << "The territories to attack: " << endl;
    for(int i = 0; i < territoryList.size(); i++){
        cout << *territoryList[i] << endl;
    }
    cout << endl;
}


void Player::toDefend(){    //defend method
    cout << "The territories to defend: " << endl;
    for(int i = 0; i < territoryList.size(); i++){
        cout << *territoryList[i] << endl;
    }
    cout << endl;
}

void Player::addTerritory(Territory* t){
    this->territoryList.push_back(t);
    t->setOwner(this);
}

void Player::issueOrder(Order* ord){
    orderList.push_back(ord);
}

void Player::printOrder(){
    cout << "Player's orders: " << endl;
    for (Order* i: orderList)
        std::cout << i << ' ';
    cout << "\n" << endl;
}

void Player::printHand(){
    cout << "Player's hands: " << endl;
    for (Hand* i: handCard)
        std::cout << i << ' ';
    cout << "\n" << endl;
}
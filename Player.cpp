#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

using namespace std;

Player::Player(){   //Default constructor
    string name;
    vector<Territory*> territory;
    vector<string> handCard;
    vector<string> orderList;
}

Player::Player(string name, vector<Territory*> territory, vector<string> handCard,vector<string> orderList){  //Constructor
    this->name = name;
    this->territory = territory;
    this->handCard = handCard;
    this->orderList = orderList;
}

Player::Player(const Player &p){    //Copy constructor
    this->name = p.name;
    this->territory = p.territory;
    this->handCard = p.handCard;
    this->orderList = p.orderList;
}

void Player::toAttack(){    //attack method
    cout << "The territories to attack: " << endl;
    for(int i = 0; i < territory.size(); i++){
        cout << *territory[i] << endl;
    }
    cout << endl;
}


void Player::toDefend(){    //defend method
    cout << "The territories to defend: " << endl;
    for(int i = 0; i < territory.size(); i++){
        cout << *territory[i] << endl;
    }
    cout << endl;
}


void Player::issueOrder(string order){
    orderList.push_back(order);
}

void Player::printOrder(){
    cout << "Player's orders: " << endl;
    for (string i: orderList)
        std::cout << i << ' ';
    cout << "\n" << endl;
}

void Player::printHand(){
    cout << "Player's hands: " << endl;
    for (string i: handCard)
        std::cout << i << ' ';
    cout << "\n" << endl;
}
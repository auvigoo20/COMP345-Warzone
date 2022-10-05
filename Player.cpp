#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

using namespace std;

Player::Player(){   //Default constructor
    string name;
    vector<Territory*> territory;
    vector<string> handCard;
    vector<Order*> orderList;
}

Player::Player(string name, vector<Territory*> territory, vector<string> handCard,vector<Order*> orderList){  //Constructor
    this->name = name;
    this->territory = territory;
    this->handCard = handCard;
    this->orderList = orderList;
}

Player::Player(const Player& p){    //Copy constructor
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


void Player::issueOrder(Order* order){
    Order *ord = new Order(order);
    orderList.push_back(ord);
}
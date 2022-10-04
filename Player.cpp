#include "Player.h"

using namespace std;

Player::Player(){   //Default constructor
    string name;
    vector<string*> territory;
    vector<string*> handCard;
    vector<Order*> orderList;
}

Player::Player(string name, vector<string*> territory, vector<string*> handCard,vector<Order*> orderList){  //Constructor
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

Player::~Player(){  //Destructor
    name.clear();
    territory.clear();
    handCard.clear();
    for (auto orderList: orderList){
        delete orderList;
    }
    orderList.clear();
    vector<string*>().swap(territory); //memory release
    vector<string*>().swap(handCard);
    vector<Order*>().swap(orderList);
}

void Player::toAttack(){    //attack method
    cout << "The territories to attack" << endl;
    for(int i = 0; i < territory.size(); i++){
        cout << *territory[i] << endl;
    }
    cout << endl;
}


void Player::toDefend(){    //defend method
    cout << "The territories to defend" << endl;
    for(int i = 0; i < territory.size(); i++){
        cout << *territory[i] << endl;
    }
    cout << endl;
}


void Player::issueOrder(string orderList){
    Order *ord = new Order(order);
    orderList.push_back(ord);
}
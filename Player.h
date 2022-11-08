#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Cards.h"
#include "Map.h"
#include "Orders.h"

using namespace std;

class Player {

public:
    Player();
    ~Player();
    Player(string name, Hand* hand, OrdersList* ordersList, int reinforcementPool);
    Player(const Player&);
    Player& operator=(const Player &p);

    vector<Territory*> getTerritories();
    Hand* getHand();
    OrdersList* getOrdersList();

    void setTerritories(vector<Territory*> territories);
    void setHand(Hand* hand);
    void setOrdersList(OrdersList* ordersList);

    void addTerritory(Territory* t);

    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    void issueOrder(int orderID);
    string getName();

private:
    friend ostream& operator<<(ostream&, const Player&);
    string name;
    vector<Territory*> ownedTerritories;
    Hand* hand;
    OrdersList* orderList;
    int reinforcementPool;
};

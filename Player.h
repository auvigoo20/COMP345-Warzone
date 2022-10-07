#include <string>
#include <vector>
#include <iostream>
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

using namespace std;

class Player {

public:
    Player();
    Player(string name);
    Player(const Player&);

    vector<Territory*> getTerritories();
    Hand* getHand();
    OrdersList* getOrdersList();

    void setTerritories(vector<Territory*> territories);
    void setHand(Hand* hand);
    void setOrdersList(OrdersList* ordersList);

    void addTerritory(Territory* t);

    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    void issueOrder();

private:
    string name;
    vector<Territory*> ownedTerritories;
    Hand* hand;
    OrdersList* orderList;
};

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
    // Default constructor
    Player(string name, vector<Territory*> territory, vector<Hand*> handCard,vector<Order*>orderList);
    // Constructor
    Player(const Player&);
    // Copy constructor

    void toAttack();
    void toDefend();
    void addTerritory(Territory* t);
    void issueOrder(Order*);
    void printOrder();
    void printHand();

private:
    string name;
    vector<Territory*> territoryList;
    vector<Hand*> handCard;
    vector<Order*> orderList;
};
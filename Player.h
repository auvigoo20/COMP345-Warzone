#include <string>
#include <vector>
#include <iostream>
#include "Map.h"

using namespace std;

class Order;

class Player {

public:
    Player();
    // Default constructor
    Player(string name, vector<Territory*> territory, vector<string> handCard,vector<Order*>);
    // Constructor
    Player(const Player&);
    // Copy constructor

    void toAttack();
    void toDefend();
    void issueOrder(Order*);

private:
    string name;
    vector<Territory*> territory;
    vector<string> handCard;
    vector<Order*> orderList;
};
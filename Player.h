#include <string>
#include <vector>
#include <iostream>
#include "Map.h"

using namespace std;

class Player {

public:
    Player();
    // Default constructor
    Player(string name, vector<Territory*> territory, vector<string> handCard,vector<string>order);
    // Constructor
    Player(const Player&);
    // Copy constructor

    void toAttack();
    void toDefend();
    void issueOrder(string);
    void printOrder();
    void printHand();

private:
    string name;
    vector<Territory*> territory;
    vector<string> handCard;
    vector<string> orderList;
};
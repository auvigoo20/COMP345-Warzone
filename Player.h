#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Order;

class Player {

public:
    Player();
    // Default constructor
    Player(string name, vector<string*> territory, vector<string*> handCard,vector<Order*>);
    // Constructor
    Player(const Player&);
    // Copy constructor
    ~Player();
    //Destructor

    void toAttack();
    void toDefend();
    void issueOrder(string);

private:
    string name;
    vector<string*> territory;
    vector<string*> handCard;
    vector<Order*> orderList;
};
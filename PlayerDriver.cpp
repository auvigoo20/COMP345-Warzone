#include "Player.h"
#include "Orders.h"

void testPlayer(){
    string name = "PLAYER";

    vector<string> orderList1;

    vector<Territory *> territory1;
    Continent* c1 = new Continent("C1", 1);
    Territory* t1 = new Territory("T1", 1, 2, c1);
    Territory* t2 = new Territory("T2", 2, 4, c1);
    Territory* t3 = new Territory("T3", 3, 6, c1);
    territory1.push_back(t1);
    territory1.push_back(t2);
    territory1.push_back(t3);

    vector<string> handcard;
    string a = "bomb";
    string b = "reinforcement";
    handcard.push_back(a);
    handcard.push_back(b);

    Player* p1 = new Player(name, territory1,handcard, orderList1);
    (*p1).issueOrder("order1");
    (*p1).issueOrder("order2");
    (*p1).issueOrder("order3");
    (*p1).issueOrder("order4");
    (*p1).toAttack();
    (*p1).toDefend();
    (*p1).printHand();
    (*p1).printOrder();

}

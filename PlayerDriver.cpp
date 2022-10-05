#include "Player.h"

void testPlayer(){
    string name = "PLAYER";

    vector<Order*> orderList1;

    vector<Territory *> territory1;
    Continent* c1 = new Continent("C1", 1);
    Territory* t1 = new Territory("T1", 1, 2, c1);

    vector<string> handcard;
    string e = "atk";
    string f = "def";
    handcard.push_back(e);
    handcard.push_back(f);

    Player* p1 = new Player(name, territory1,handcard, orderList1);
    (*p1).toAttack();
    (*p1).toDefend();

    Player* p2 = new Player(*p1);
    (*p2).toAttack();
}

int main(){
    testPlayer();
}

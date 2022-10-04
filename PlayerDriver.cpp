#include "Player.h"

void testPlayer(){
    string name = "PLAYER";
    vector<Order*> orderList;
    vector<string*> territory;
    string c = "A";
    string d = "B";
    territory.push_back(&c);
    territory.push_back(&d);

    vector<string*> handcard;
    string e = "atk";
    string f = "def";
    handcard.push_back(&e);
    handcard.push_back(&f);

    Player* p1 = new Player(name, territory,handcard, orderList);
    (*p1).toAttack();
    (*p1).toDefend();
    (*p1).issueOrder("AAA");
    (*p1).issueOrder("BBB");
    (*p1).issueOrder("CCC");

    Player* p2 = new Player(*p1);
    (*p2).toAttack();
}

int main(){
    testPlayer();
}

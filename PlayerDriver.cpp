#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include "Map.h"

void testPlayer() {

    cout << "****************************************" << endl;
    cout << "*              PLAYER TEST             *" << endl;
    cout << "****************************************" << endl;

    vector<Territory *> territory1;
    Continent *c1 = new Continent("C1", 1);
    Territory *t1 = new Territory("T1", 1, 2, c1);
    Territory *t2 = new Territory("T2", 2, 4, c1);
    Territory *t3 = new Territory("T3", 3, 6, c1);
    Territory *t4 = new Territory("T4", 3, 6, c1);

    Hand* hand = new Hand();
    OrdersList* ordersList = new OrdersList();

    Player *p1 = new Player("Player1", hand, ordersList);
    p1->addTerritory(t1);
    p1->addTerritory(t2);
    p1->addTerritory(t3);
    p1->addTerritory(t4);

    vector<Territory *> territoriesToAttack = p1->toAttack();
    vector<Territory *> territoriesToDefend = p1->toDefend();

    cout << "Territories to attack: " << endl;
    for(auto territory:territoriesToAttack){
        cout << *territory << endl;
    }

    cout << "Territories to defend: " << endl;
    for(auto territory:territoriesToDefend){
        cout << *territory << endl;
    }

    cout << "Player1 Issuing 3 orders!" << endl;
    p1->issueOrder(0);
    p1->issueOrder(1);
    p1->issueOrder(2);

    cout << "Player information: " << endl;
    cout << *p1 << endl;

    delete c1;
    delete t1;
    delete t2;
    delete t3;
    delete p1;
    c1 = nullptr;
    t1 = nullptr;
    t2 = nullptr;
    t3 = nullptr;
    p1 = nullptr;



}

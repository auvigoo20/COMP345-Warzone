#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include "Map.h"

void testPlayer(){
    string name = "PLAYER";

    vector<Territory *> territory1;
    Continent* c1 = new Continent("C1", 1);
    Territory* t1 = new Territory("T1", 1, 2, c1);
    Territory* t2 = new Territory("T2", 2, 4, c1);
    Territory* t3 = new Territory("T3", 3, 6, c1);

    Bomb* bomb1 = new Bomb();
    Reinforcement* hand_Reinforcement = new Reinforcement();
    Blockade* hand_Blockade;
    Airlift* hand_Airlift;
    Diplomacy* hand_Diplomacy;

    Deck* deckList = new Deck();
    deckList->addCard(bomb1);

    vector<Order*> OrderList1;
    Deploy* hand_deploy = new Deploy();
    Advance* hand_advance = new Advance();
    Blockade Order_Blockade;
    Airlift Order_Airlift;
    Negotiate Order_Negotiate;
    OrderList1.push_back(&Order_Blockade);
    OrderList1.push_back(&Order_Airlift);
    OrderList1.push_back(&Order_Negotiate);

    cout << "========================================PLAYER=PART============================================" <<endl;

    Player* p1 = new Player(name, territory1,handcard, orderList1);
    (*p1).addTerritory(t1);
    (*p1).addTerritory(t2);
    (*p1).addTerritory(t3);
    (*p1).issueOrder(&Order_Blockade);
    (*p1).issueOrder(&Order_Airlift);
    (*p1).issueOrder(&Order_Negotiate);
    (*p1).toAttack();
    (*p1).toDefend();
    (*p1).printHand();
    (*p1).printOrder();
}

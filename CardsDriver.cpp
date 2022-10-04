#include "CardsDriver.h"
#include "Cards.h"
#include <iostream>

using std::cout;
using std::endl;

int testCards(){
    cout << "Testing Cards, HandLists and DeckLists" << endl;


    //creating different type of Cards

    Bomb* bomb1 = new Bomb();
    Bomb* bomb2 = new Bomb();

    Reinforcement* reinforcement1 = new Reinforcement();
    Reinforcement* reinforcement2 = new Reinforcement();

    Blockade* blockade1 = new Blockade();
    Blockade* blockade2 = new Blockade();

    Airlift* airlift1 = new Airlift();
    Airlift* airlift2 = new Airlift();

    Diplomacy* diplomacy1 = new Diplomacy();
    Diplomacy* diplomacy2 = new Diplomacy();

    //creating deck

    Deck* deckList = new Deck();

    //adding all cards in deck

    deckList->addCard(bomb1);
    deckList->addCard(bomb2);
    deckList->addCard(reinforcement1);
    deckList->addCard(reinforcement2);
    deckList->addCard(blockade1);
    deckList->addCard(blockade2);
    deckList->addCard(airlift1);
    deckList->addCard(airlift2);
    deckList->addCard(diplomacy1);
    deckList->addCard(diplomacy2);

    cout << *deckList;

    //creating player 1 hand list

    Hand* handList1  = new Hand(deckList);

    //creating player 2 hand list

    Hand* handList2 = new Hand(deckList);

    cout << "//testing draw() method on player 1 hand list" << endl;

    deckList->draw(handList1);

    cout <<*deckList << endl;
    cout <<*handList1 << endl;

    cout << "//testing player play() method on this card" << endl;

    handList1->playCard(1);

    cout <<*deckList << endl;
    cout <<*handList1 << endl;



    return 0;
}
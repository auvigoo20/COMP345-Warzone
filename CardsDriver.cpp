#include "CardsDriver.h"
#include "Cards.h"
#include <iostream>

using std::cout;
using std::endl;

int testCards(){
    cout << "Testing Cards, HandLists and DeckLists" << endl;


    //creating different type of Cards

    BombCard* bomb1 = new BombCard();
    BombCard* bomb2 = new BombCard();

    ReinforcementCard* reinforcement1 = new ReinforcementCard();
    ReinforcementCard* reinforcement2 = new ReinforcementCard();

    BlockadeCard* blockade1 = new BlockadeCard();
    BlockadeCard* blockade2 = new BlockadeCard();

    AirliftCard* airlift1 = new AirliftCard();
    AirliftCard* airlift2 = new AirliftCard();

    DiplomacyCard* diplomacy1 = new DiplomacyCard();
    DiplomacyCard* diplomacy2 = new DiplomacyCard();

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
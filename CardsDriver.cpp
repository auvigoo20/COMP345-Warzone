#include "CardsDriver.h"
#include "Cards.h"
#include "Player.h"
#include <iostream>

using std::cout;
using std::endl;

int testCards(){
    cout << "****************************************" << endl;
    cout << "*    Testing Cards, Hands and Decks    *" << endl;
    cout << "****************************************" << endl;

    /**
     * Creating different type of Cards
     */

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

    /**
     * Creating a Deck
     */

    Deck* deck = new Deck();

    /**
     * Adding all created Cards in the common Deck
     */

    deck->addCard(bomb1);
    deck->addCard(bomb2);
    deck->addCard(reinforcement1);
    deck->addCard(reinforcement2);
    deck->addCard(blockade1);
    deck->addCard(blockade2);
    deck->addCard(airlift1);
    deck->addCard(airlift2);
    deck->addCard(diplomacy1);
    deck->addCard(diplomacy2);


    cout << *deck;

    /**
     * Creating first player Hand
     */
    Hand* hand1  = new Hand(deck);

    /**
     * Create dummy player
     */

    OrdersList* ordersList = new OrdersList();
    Player* player = new Player("Bobby", hand1, ordersList);
    hand1->setOwner(player);

    /**
     * Testing draw() method on first player Hand ; player draw a Card and places it in his Hands
     */

    cout << "Calling draw() for player Bobby" << endl;

    deck->draw(hand1);
    deck->draw(hand1);
    deck->draw(hand1);

    cout << *deck << endl;
    cout << *hand1 << endl;

    /**
     * Testing play() method with first player Hand
     */

    cout << "Player Bobby calling the play() method on this card" << endl;
    Continent* continent = new Continent("RandomCont", 5);
    Territory* territory = new Territory("randomTer", 1, 2, continent);

    hand1->playCard(1, territory);
    hand1->playCard(1, territory);
    hand1->playCard(1, territory);

    cout << *deck << endl;
    cout << *hand1 << endl;

    cout << "Check if the order associated with the played card is in the Player's orderlist" << endl;
    cout << *player->getOrdersList() << endl;

    return 0;
}

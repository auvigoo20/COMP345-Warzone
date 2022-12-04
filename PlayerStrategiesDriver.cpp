#include <iostream>

#include "PlayerStrategiesDriver.h"
#include "Player.h"

using std::cout;
using std::endl;

int testPlayerStrategies() {

    cout << "*****************************************" << endl;
    cout << "*        Testing Player's Strategies    *" << endl;
    cout << "*****************************************" << endl;

    cout << "-- Test that right behaviour is displayed by the player when strategy is set. --\n" << endl;

    //Create necessary object to test the orders' execution

    Deck* deck = new Deck();

    Hand* hand1 = new Hand();
    Hand* hand2 = new Hand();

    OrdersList* ordersList1 = new OrdersList();
    OrdersList* ordersList2 = new OrdersList();

    Player* player1 = new Player("Current Player", hand1, ordersList1, 10);
    Player* player2 = new Player("Enemy Player", hand2, ordersList2, 10);

    player1->getOpponentPlayerList().push_back(player2);

    hand1->setOwner(player1);
    hand2->setOwner(player2);

    hand1->setDeckList(deck);
    hand2->setDeckList(deck);

    BombCard* bombCard = new BombCard();
    BlockadeCard* blockadeCard = new BlockadeCard();
    AirliftCard* airliftCard = new AirliftCard();
    DiplomacyCard* diplomacyCard = new DiplomacyCard();
    ReinforcementCard* reinforcementCard = new ReinforcementCard();

    player1->getHand()->addCard(bombCard);
    player1->getHand()->addCard(blockadeCard);
    player1->getHand()->addCard(airliftCard);
    player1->getHand()->addCard(diplomacyCard);
    player1->getHand()->addCard(reinforcementCard);

    HumanPlayerStrategy* humanStrategy = new HumanPlayerStrategy(player1);
    player1->setPlayerStrategy(humanStrategy);

    Continent* continent =  new Continent("Africa", 12);
    Territory* ownedTerritory1 = new Territory("ownedTerritory1", 1, 1, continent);
    Territory* enemyTerritory1 = new Territory("enemyTerritory1", 1, 2, continent);
    Territory* enemyNonAdjacentTer = new Territory("enemyNonAdjacentTer", 20, 10, continent);
    Territory* alliedNonAdjacentTer = new Territory("alliedNonAdjacentTer", 12, 12, continent);
    Territory* alliedAdjacentTer = new Territory("alliedAdjacentTer", 2, 1, continent);

    player1->addTerritory(ownedTerritory1);
    player1->addTerritory(alliedAdjacentTer);
    player1->addTerritory(alliedNonAdjacentTer);
    player2->addTerritory(enemyTerritory1);
    player2->addTerritory(enemyNonAdjacentTer);

    ownedTerritory1->addAdjacentTerritory(enemyTerritory1);
    ownedTerritory1->addAdjacentTerritory(alliedAdjacentTer);


    bool endPhase = false;
    while(!endPhase) {
        endPhase = player1->issueOrder(true);
    }

    endPhase = false;
    while(!endPhase) {
        endPhase = player1->issueOrder(false);
    }

    return 0;
}

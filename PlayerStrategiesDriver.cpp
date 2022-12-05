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

    BombCard* bombCard2 = new BombCard();
    BlockadeCard* blockadeCard2 = new BlockadeCard();
    AirliftCard* airliftCard2 = new AirliftCard();
    DiplomacyCard* diplomacyCard2 = new DiplomacyCard();
    ReinforcementCard* reinforcementCard2 = new ReinforcementCard();

    player1->getHand()->addCard(bombCard);
    player1->getHand()->addCard(blockadeCard);
    player1->getHand()->addCard(airliftCard);
    player1->getHand()->addCard(diplomacyCard);
    player1->getHand()->addCard(reinforcementCard);


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

    player1->setOpponentPlayerList({player2});
    player2->setOpponentPlayerList({player1});

    ownedTerritory1->addAdjacentTerritory(enemyTerritory1);
    ownedTerritory1->addAdjacentTerritory(alliedAdjacentTer);
    alliedAdjacentTer->addAdjacentTerritory(ownedTerritory1);
    enemyTerritory1->addAdjacentTerritory(ownedTerritory1);


    HumanPlayerStrategy* humanStrategy = new HumanPlayerStrategy(player1);
    AggressivePlayerStrategy* aggressivePlayerStrategy = new AggressivePlayerStrategy(player1);
    BenevolentPlayerStrategy* benevolentPlayerStrategy = new BenevolentPlayerStrategy(player1);
    CheaterPlayerStrategy* cheaterStrategy = new CheaterPlayerStrategy(player1);
    NeutralPlayerStrategy* neutralStrategy = new NeutralPlayerStrategy(player2);

    cout << "\n --- Testing human player strategy ---" << endl;

    player1->setPlayerStrategy(humanStrategy);
    bool endPhase = false;
    while(!endPhase) {
        endPhase = player1->issueOrder(true);
    }

    endPhase = false;
    while(!endPhase) {
        endPhase = player1->issueOrder(false);
    }

    cout << "\n --- Testing aggressive player strategy ---" << endl;

    player1->setPlayerStrategy(aggressivePlayerStrategy);
    endPhase = false;
    while(!endPhase) {
        endPhase = player1->issueOrder(true);
    }

    endPhase = false;
    while(!endPhase) {
        endPhase = player1->issueOrder(false);
    }

    player1->getHand()->addCard(bombCard2);
    player1->getHand()->addCard(blockadeCard2);
    player1->getHand()->addCard(airliftCard2);
    player1->getHand()->addCard(diplomacyCard2);
    player1->getHand()->addCard(reinforcementCard2);

    cout << "\n --- Testing benevolent player strategy ---" << endl;

    player1->setPlayerStrategy(benevolentPlayerStrategy);
    ownedTerritory1->setNumOfArmies(10);
    endPhase = false;
    while(!endPhase) {
        endPhase = player1->issueOrder(true);
    }

    endPhase = false;
    while(!endPhase) {
        endPhase = player1->issueOrder(false);
    }

    cout << "\n --- Testing cheating player strategy ---" << endl;
    player1->setPlayerStrategy(cheaterStrategy);
    player1->setReinforcementPool(10);
    endPhase = false;
    while(!endPhase) {
        endPhase = player1->issueOrder(true);
    }

    endPhase = false;
    while(!endPhase) {
        endPhase = player1->issueOrder(false);
    }


    cout << "\n --- Testing neutral player strategy ---" << endl;
    player1->removeTerritory(enemyTerritory1);
    enemyTerritory1->setOwner(player2);
    player2->addTerritory(enemyTerritory1);
    player1->setReinforcementPool(10);
    player2->setPlayerStrategy(neutralStrategy);
    cout << "Player 2 strategy type: " << player2->getPlayerStrategy()->getStrategyType() << endl;

    // Create offensive advance order on player2 who is now 'Neutral'
    Advance* advanceOrder = new Advance(player1, 10, ownedTerritory1, enemyTerritory1);
    // Should change player2 strategy to aggressive.
    advanceOrder->execute();
    cout << "Player 2 strategy type: " << player2->getPlayerStrategy()->getStrategyType() << endl;

    delete player1;
    delete player2;
    delete deck;
    delete continent;
    delete ownedTerritory1;
    delete alliedNonAdjacentTer;
    delete alliedAdjacentTer;
    delete enemyTerritory1;
    delete enemyNonAdjacentTer;

    return 0;
}

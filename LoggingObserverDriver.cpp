#include "LoggingObserverDriver.h"
#include "LoggingObserver.h"
#include "CommandProcessing.h"
#include "GameEngine.h"
#include "Player.h"

void testLoggingObserver(){

    LogObserver* logObserver = new LogObserver();

    // TESTING COMMAND AND COMMAND PROCESSOR
    GameEngine* gameEngine = new GameEngine();
    CommandProcessor* commandProcessor = new CommandProcessor(gameEngine);
    commandProcessor->attach(logObserver);

    for(int i = 0 ; i < 3; i++){
        Command* cmd = commandProcessor->getCommand();
        cmd->attach(logObserver);
        cmd->saveEffect("Command effect test");
    }
    delete gameEngine;
    delete commandProcessor;
    gameEngine = nullptr;
    commandProcessor = nullptr;

    // TESTING CHANGE OF STATE

    GameEngine* ge = new GameEngine();
    ge->attach(logObserver);
    ge->setCurrentState(ge->start);
    ge->setCurrentState(ge->mapLoaded);
    delete ge;
    ge = nullptr;

    // TESTING ORDERS LIST AND ORDERS
    // Creating needed objects
    Hand* hand = new Hand();
    OrdersList* ordersList = new OrdersList();
    ordersList->attach(logObserver);
    Player* player = new Player("Current Player", hand, ordersList, 10);
    hand->setOwner(player);
    Hand* enemyHand = new Hand();
    OrdersList* enemyOrdersList = new OrdersList();
    Player* enemyPlayer = new Player("Enemy Player", enemyHand, enemyOrdersList, 10);
    enemyHand->setOwner(enemyPlayer);

    Continent* continent =  new Continent("Africa", 12);
    Territory* ownedTerritory1 = new Territory("ownedTerritory1", 1, 1, continent);
    ownedTerritory1->setNumOfArmies(40);
    Territory* ownedTerritory2 = new Territory("ownedTerritory2", 2, 1, continent);
    ownedTerritory2->setNumOfArmies(10);
    Territory* enemyTerritory = new Territory("enemyTerritory", 1, 2, continent);
    enemyTerritory->setNumOfArmies(10);
    player->addTerritory(ownedTerritory1);
    player->addTerritory(ownedTerritory2);
    enemyPlayer->addTerritory(enemyTerritory);
    ownedTerritory1->addAdjacentTerritory(ownedTerritory2);
    ownedTerritory1->addAdjacentTerritory(enemyTerritory);

    Order* bombOrder = new Bomb(player, enemyTerritory);
    bombOrder->attach(logObserver);

    Order* deployOrder = new Deploy(player, 5, ownedTerritory1);
    deployOrder->attach(logObserver);

    Order* advanceOrder1 = new Advance(player, 20, ownedTerritory1, enemyTerritory);
    Order* advanceOrder2 = new Advance(player, 5, ownedTerritory1, ownedTerritory2);
    advanceOrder1->attach(logObserver);
    advanceOrder2->attach(logObserver);

    Order* airliftOrder = new Airlift(player, 5, ownedTerritory1, ownedTerritory2);
    airliftOrder->attach(logObserver);

    Order* blockadeOrder = new Blockade(player, ownedTerritory2);
    blockadeOrder->attach(logObserver);

    Order* negotiateOrder = new Negotiate(player, enemyPlayer);
    negotiateOrder->attach(logObserver);


    // Adding orders to list
    ordersList->addOrder(bombOrder);
    ordersList->addOrder(deployOrder);
    ordersList->addOrder(advanceOrder1);
    ordersList->addOrder(advanceOrder2);
    ordersList->addOrder(airliftOrder);
    ordersList->addOrder(blockadeOrder);
    ordersList->addOrder(negotiateOrder);

    // Executing orders
   for(auto* order: ordersList->getOrdersList()) {
       order->execute();
   }



}

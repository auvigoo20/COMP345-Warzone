#include "OrdersDriver.h"
#include "Orders.h"
#include "Player.h"
#include "Cards.h"
#include <iostream>

using std::cout;
using std::endl;

int testOrdersLists(){
    cout << "*****************************************" << endl;
    cout << "* Testing Orders and OrdersList classes *" << endl;
    cout << "*****************************************" << endl;

    //Creating multiple territories needed to create orders.

    Continent* continent =  new Continent("Africa", 12);
    Territory* ter1 = new Territory("Canada", 12, 13, continent);
    ter1->setNumOfArmies(10);
    Territory* ter2 = new Territory("USA", 12, 14, continent);
    ter2->setNumOfArmies(10);
    Territory* ter3 = new Territory("France", 12, 13, continent);
    ter3->setNumOfArmies(10);
    Territory* ter4 = new Territory("Mexico", 12, 13, continent);
    ter4->setNumOfArmies(10);
    Territory* ter5 = new Territory("Quebec", 12, 13, continent);
    ter5->setNumOfArmies(30);
    Territory* ter6 = new Territory("Ontario", 12, 13, continent);
    ter6->setNumOfArmies(10);

    // Creation of two OrdersList objects for testing

    OrdersList* list1 = new OrdersList();
    OrdersList* testList = new OrdersList();
    OrdersList list2;

    // Creation of a hand object
    Hand* hand = new Hand();
    Hand* hand2 = new Hand();

    // Creation of the player

    Player* player = new Player("John", hand, list1, 3);
    Player* player2 = new Player("Bob", hand2, testList, 3);

    // Creating different all type of orders using different constructors

    Deploy* dep2 = new Deploy(player, 12, ter1);
    ter1->setOwner(player);

    Advance* adv2 = new Advance(player, 16, ter1, ter2);
    ter2->setOwner(player2);

    Bomb* bomb2 = new Bomb(player, ter3);

    Blockade* block2 = new Blockade(player, ter4);

    Airlift* air2 = new Airlift(player, 22, ter5, ter6);
    ter5->setOwner(player);
    ter6->setOwner(player);

    Negotiate* neg1 = new Negotiate();


    // Orders added to list1 in that order
    list1->addOrder(dep2);
    list1->addOrder(adv2);
    list1->addOrder(bomb2);
    list1->addOrder(block2);
    list1->addOrder(air2);
    list1->addOrder(neg1);

    //Testing OrdersList moveOrder functions:
    cout << " -- Testing OrdersList moveOrder functions -- " << endl;
    cout << "Expected list order:" << endl;
    cout << "Advance, deploy, block, bomb, air, negotiate" << endl;
    list1->moveOrderDown(1);
    list1->moveOrderUp(4);
    cout << *list1;
    cout << "Expected: Element already on top message" << endl;
    list1->moveOrderUp(1);
    cout << "Expected: Element already bottom message" << endl;
    list1->moveOrderDown(6);
    cout << endl;

    //Testing OrdersList removeOrder function:
    cout << " -- Testing OrdersList removeOrder function --" << endl;
    list1->removeOrder(6);
    cout << "Advance, deploy, block, bomb, air" << endl;
    cout << *list1;

    //Testing Orders execute function:
    cout << "Testing Orders execute function:" << endl;
    cout << "All orders in list1 must be validated and executed in order." << endl;
    for(int i = 1; i <= list1->getSize(); i++) {
        cout << i << " - ";
        list1->getOrder(i)->execute();
        cout << endl;
    }

    //Testing assignment operators:
    cout << "Testing assignment operator" << endl;
    list2 = *list1;

    cout << *list1 << endl;
    list1->removeOrder(1);

    cout << "LIST 1 EXPECTED: Deploy, Blockade, Bombing, Airlift" << endl;
    cout << *list1 << endl;
    cout << "LIST 2 EXPECTED: Advance, Deploy, Blockade, Bombing, Airlift" << endl;
    cout << list2 << endl;
    cout << "Size of list 1 expected 4." << endl;
    cout << list1->getSize() << endl;
    cout << "Size of list 2 expected 5" << endl;
    cout << list2.getSize() << endl;

    delete continent;
    delete ter1;
    delete ter2;
    delete ter3;
    delete ter4;
    delete ter5;
    delete ter6;
    delete player;
    delete player2;

    return 0;
}

int testOrderExecution(){

    cout << "*****************************************" << endl;
    cout << "*        Testing Orders' Execution       *" << endl;
    cout << "*****************************************" << endl;

    cout << "-- Test that orders are verified before execution --\n" << endl;

    //Create necessary object to test the orders' execution

    Hand* hand1 = new Hand();
    Hand* hand2 = new Hand();

    OrdersList* ordersList1 = new OrdersList();
    OrdersList* ordersList2 = new OrdersList();

    Player* player1 = new Player("Current Player", hand1, ordersList1, 10);
    Player* player2 = new Player("Enemy Player", hand2, ordersList2, 10);

    hand1->setOwner(player1);
    hand2->setOwner(player2);

    Continent* continent =  new Continent("Africa", 12);
    Territory* ownedTerritory1 = new Territory("ownedTerritory1", 1, 1, continent);
    Territory* enemyTerritory1 = new Territory("enemyTerritory1", 1, 2, continent);
    Territory* enemyNonAdjacentTer = new Territory("enemyNonAdjacentTer", 20, 10, continent);
    Territory* alliedNonAdjacentTer = new Territory("alliedNonAdjacentTer", 12, 12, continent);
    Territory* alliedAdjacentTer = new Territory("alliedAdjacentTer", 2, 1, continent);

    ownedTerritory1->setOwner(player1);
    alliedNonAdjacentTer->setOwner(player1);
    alliedAdjacentTer->setOwner(player1);
    enemyTerritory1->setOwner(player2);
    enemyNonAdjacentTer->setOwner(player2);

    ownedTerritory1->addAdjacentTerritory(enemyTerritory1);
    ownedTerritory1->addAdjacentTerritory(alliedAdjacentTer);

    // *********** TESTING DEPLOY ORDER VALIDATION
    cout << "Testing Deploy order\n" << endl;

    cout << "Valid Deploy Order" << endl;
    Order* validDeploy = new Deploy(player1, 3, ownedTerritory1);
    validDeploy->execute();
    cout << "\n" << endl;

    cout << "Invalid Deploy Order" << endl;
    Order* invalidDeploy = new Deploy(player1, 3, enemyTerritory1);
    invalidDeploy->execute();
    cout << "\n" << endl;

    // *********** TESTING ADVANCE ORDER VALIDATION
    cout << "Testing Advance order\n" << endl;

    cout << "Valid Advance Order" << endl;
    Order* validAdvance = new Advance(player1, 4, ownedTerritory1, alliedAdjacentTer);
    validAdvance->execute();
    cout << "\n" << endl;

    cout << "Invalid Advance Order (Target territory not adjacent to source):" << endl;
    Order* invalidAdvance = new Advance(player1, 4, ownedTerritory1, enemyNonAdjacentTer);
    invalidAdvance->execute();
    cout << "\n" << endl;

    cout << "Invalid Advance Order (Source territory not owned):" << endl;
    Order* invalidAdvance2 = new Advance(player1, 4, enemyTerritory1, ownedTerritory1);
    invalidAdvance2->execute();
    cout << "\n" << endl;


    // TESTING AIRLIFT ORDER VALIDATION
    cout << "Testing Airlift order\n" << endl;

    cout << "Valid Airlift Order" << endl;
    Order* validAirlift = new Airlift(player1, 5, ownedTerritory1, alliedNonAdjacentTer);
    validAirlift->execute();
    cout << "\n" << endl;

    cout << "Invalid Airlift Order (Source territory not owned)" << endl;
    Order* invalidAirliftOrder = new Airlift(player1, 5, enemyTerritory1, ownedTerritory1);
    invalidAirliftOrder->execute();
    cout << "\n" << endl;

    cout << "Invalid Airlift Order (Target territory not owned)" << endl;
    Order* invalidAirliftOrder2 = new Airlift(player1, 5, ownedTerritory1, enemyTerritory1);
    invalidAirliftOrder2->execute();
    cout << "\n" << endl;



    cout << " -- Testing that territory ownership is transferred given successful attack" << endl;
    Order* successfulAttack = new Advance(player1, 5, ownedTerritory1, enemyTerritory1);
    cout << "Print 'enemyTerritory1 owner before successful attack" << endl;
    cout << enemyTerritory1->getOwner()->getName() << endl;
    successfulAttack->execute();
    cout << "Print 'enemyTerritory1 owner after successful attack" << endl;
    cout << enemyTerritory1->getOwner()->getName() << endl;
    cout << "\n" << endl;

    return 0;
}
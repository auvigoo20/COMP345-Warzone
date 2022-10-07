#include "OrdersDriver.h"
#include "Orders.h"
#include <iostream>

using std::cout;
using std::endl;

int testOrdersLists(){
    cout << "-------------------------------------" << endl;
    cout << "Testing Orders and OrdersList classes" << endl;
    cout << "-------------------------------------" << endl;

    // Creating different all type of orders using different constructors
    Continent* continent =  new Continent("Africa", 12);
    Territory* ter1 = new Territory("Canada", 12, 13, continent);
    Territory* ter2 = new Territory("USA", 13, 14, continent);
    Territory* ter3 = new Territory("France", 12, 13, continent);
    Territory* ter4 = new Territory("Mexico", 12, 13, continent);
    Territory* ter5 = new Territory("Quebec", 12, 13, continent);
    Territory* ter6 = new Territory("Ontario", 12, 13, continent);
    Deploy* dep1 = new Deploy();
    Deploy* dep2 = new Deploy(12, ter1);

    Advance* adv1 = new Advance();
    Advance* adv2 = new Advance(10, ter1, ter2);

    Bomb* bomb1 = new Bomb();
    Bomb* bomb2 = new Bomb(ter3);

    Blockade* block1 = new Blockade();
    Blockade* block2 = new Blockade(ter4);

    Airlift* air1 = new Airlift();
    Airlift* air2 = new Airlift(22, ter5, ter6);

    Negotiate* neg1 = new Negotiate();
    Negotiate* neg2 = new Negotiate("Johnny");

    // Creation of two OrdersList objects for testing

    OrdersList* list1 = new OrdersList();
    OrdersList list2;

    // Orders added to list1 in that order
    list1->addOrder(dep1);
    list1->addOrder(adv1);
    list1->addOrder(bomb1);
    list1->addOrder(block1);
    list1->addOrder(air1);
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

    cout << list1 << endl;
    list1->removeOrder(1);

    cout << "LIST 1 EXPECTED: Deploy, Blockade, Bombing, Airlift" << endl;
    cout << *list1 << endl;
    cout << "LIST 2 EXPECTED: Advance, Deploy, Blockade, Bombing, Airlift" << endl;
    cout << list2 << endl;
    cout << "Size of list 1 expected 4." << endl;
    cout << list1->getSize() << endl;
    cout << "Size of list 2 expected 5" << endl;
    cout << list2.getSize() << endl;
    return 0;
}
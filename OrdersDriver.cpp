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

    Deploy* dep1 = new Deploy();
    Deploy* dep2 = new Deploy(12, "Canada");

    Advance* adv1 = new Advance();
    Advance* adv2 = new Advance(10, "Canada", "USA");

    Bomb* bomb1 = new Bomb();
    Bomb* bomb2 = new Bomb("France");

    Blockade* block1 = new Blockade();
    Blockade* block2 = new Blockade("Mexico");

    Airlift* air1 = new Airlift();
    Airlift* air2 = new Airlift(22, "Quebec", "Ontario");

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
    cout << *list1 << endl;
    list1->removeOrder(1);

    cout << *list1 << endl;
    cout << list2 << endl;
    cout << list2 << endl;

    return 0;
}
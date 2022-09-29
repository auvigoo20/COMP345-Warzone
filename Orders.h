#pragma once
#include <iostream>
#include <vector>

using namespace std;

// Forward declaration
class OrdersList;

class Order {
    public:
        Order( );
};

class OrdersList {

    public:
        OrdersList( );
        vector<Order*> ordersList;
        void addOrder(Order* order);
};


class Deploy: public Order {
    public:

};

class Advance: public Order {
    public:

};

class Bomb: public Order {
    public:

};

class Blockade: public Order {
    public:

};

class Airlift: public Order {
    public:

};

class Negotiate: public Order {
    public:

};
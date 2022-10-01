#pragma once
#include <iostream>
#include <vector>

using namespace std;

// Forward declaration
class OrdersList;

class Order
{
public:
    virtual ostream& printOrder(ostream& output) const = 0;
    virtual bool validate() const = 0;
    virtual void execute() const = 0;
    virtual ~Order() = default;

private:
    friend ostream& operator << (ostream& output, Order& o);
};

class OrdersList
{
public:
    OrdersList( );
    OrdersList(const OrdersList& o);
    void addOrder(Order* order);
    void removeOrder(int index);
    void moveOrderUp(int index);
    void moveOrderDown(int index);
    void executeOrders();
    int getSize();
    ostream& printList(ostream& output);
    Order* getOrder(int index);
    ~OrdersList();

private:
    vector<Order*> ordersList;
    friend ostream& operator << (ostream& output, OrdersList& o);
};


class Deploy: public Order
{
public:
    Deploy( );
    Deploy(const Deploy& d);
    Deploy(int numOfArmies, string targetTerritory);
    ostream& printOrder(ostream& output) const override;
    void execute() const override;
    bool validate() const override;
    ~Deploy() override = default;

private:
    int numOfArmies;
    string targetTerritory; //***** Has to be changed to Territory object ptr *****

};

class Advance: public Order
{
public:
    Advance( );
    Advance(const Advance& a);
    Advance(int numOfArmies, string sourceTerritory, string targetTerritory);
    ostream& printOrder(ostream& output) const override;
    void execute() const override;
    bool validate() const override;
    ~Advance();

private:
    int numOfArmies;
    string sourceTerritory; //***** Has to be changed to Territory object ptr *****
    string targetTerritory; //***** Has to be changed to Territory object ptr *****

};

class Bomb: public Order
{
public:
    Bomb( );
    Bomb(const Bomb& b);
    Bomb(string* targetTerritory);
    ostream& printOrder(ostream& output) const override;
    void execute() const override;
    bool validate() const override;
    ~Bomb();

private:
    string* targetTerritory; //***** Has to be changed to Territory object ptr *****

};

class Blockade: public Order
{
public:
    Blockade( );
    Blockade(const Blockade& b);
    Blockade(string* targetTerritory);
    ostream& printOrder(ostream& output) const override;
    void execute() const override;
    bool validate() const override;
    ~Blockade();

private:
    string* targetTerritory; //***** Has to be changed to Territory object ptr *****

};

class Airlift: public Order {
public:
    Airlift( );
    Airlift(const Airlift& b);
    Airlift(int numOfArmies, string* sourceTerritory, string* targetTerritory);
    ostream& printOrder(ostream& output) const override;
    void execute() const override;
    bool validate() const override;
    ~Airlift();

private:
    int numOfArmies;
    string* sourceTerritory; //***** Has to be changed to Territory object ptr *****
    string* targetTerritory; //***** Has to be changed to Territory object ptr *****

};

class Negotiate: public Order {
public:
    Negotiate( );
    Negotiate(const Negotiate& b);
    Negotiate(string* targetPlayer);
    ostream& printOrder(ostream& output) const override;
    void execute() const override;
    bool validate() const override;
    ~Negotiate();

private:
    string* targetPlayer;

};
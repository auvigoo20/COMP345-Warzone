#pragma once
#include <iostream>
#include <vector>
#include "Map.h"

using namespace std;

// Forward declaration
class OrdersList;

class Order
{
public:
    virtual ostream& printOrder(ostream& output) const = 0;
    virtual bool validate() const = 0;
    virtual void execute() const = 0;
    virtual Order* copy() const = 0;
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
    OrdersList& operator = (const OrdersList& o);
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
    Deploy(int numOfArmies, Territory* targetTerritory);
    ostream& printOrder(ostream& output) const override;
    void execute() const override;
    bool validate() const override;
    Deploy* copy() const  override;
    Deploy& operator = (const Deploy& d);
    ~Deploy() override;

private:
    int numOfArmies;
    Territory* targetTerritory; //***** Has to be changed to Territory object ptr *****
};

class Advance: public Order
{
public:
    Advance( );
    Advance(const Advance& a);
    Advance(int numOfArmies, Territory* sourceTerritory, Territory* targetTerritory);
    ostream& printOrder(ostream& output) const override;
    void execute() const override;
    bool validate() const override;
    Advance* copy() const  override;
    Advance& operator = (const Advance& a);
    ~Advance() override;

private:
    int numOfArmies;
    Territory* sourceTerritory; //***** Has to be changed to Territory object ptr *****
    Territory* targetTerritory; //***** Has to be changed to Territory object ptr *****
};

class Bomb: public Order
{
public:
    Bomb( );
    Bomb(const Bomb& b);
    explicit Bomb(Territory* targetTerritory);
    ostream& printOrder(ostream& output) const override;
    void execute() const override;
    bool validate() const override;
    Bomb* copy() const  override;
    Bomb& operator = (const Bomb& b);
    ~Bomb() override;

private:
    Territory* targetTerritory; //***** Has to be changed to Territory object ptr *****

};

class Blockade: public Order
{
public:
    Blockade( );
    Blockade(const Blockade& b);
    explicit Blockade(Territory* targetTerritory);
    ostream& printOrder(ostream& output) const override;
    void execute() const override;
    bool validate() const override;
    Blockade* copy() const  override;
    Blockade& operator = (const Blockade& b);
    ~Blockade() override;

private:
    Territory* targetTerritory; //***** Has to be changed to Territory object ptr *****
};

class Airlift: public Order {
public:
    Airlift( );
    Airlift(const Airlift& b);
    Airlift(int numOfArmies, Territory* sourceTerritory, Territory* targetTerritory);
    ostream& printOrder(ostream& output) const override;
    void execute() const override;
    bool validate() const override;
    Airlift* copy() const  override;
    Airlift& operator = (const Airlift& a);
    ~Airlift() override;

private:
    int numOfArmies;
    Territory* sourceTerritory; //***** Has to be changed to Territory object ptr *****
    Territory* targetTerritory; //***** Has to be changed to Territory object ptr *****
};

class Negotiate: public Order {
public:
    Negotiate( );
    Negotiate(const Negotiate& b);
    explicit Negotiate(string targetPlayer);
    ostream& printOrder(ostream& output) const override;
    void execute() const override;
    bool validate() const override;
    Negotiate* copy() const  override;
    Negotiate& operator = (const Negotiate& n);
    ~Negotiate() override;

private:
    string targetPlayer;
};
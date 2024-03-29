#pragma once
#include <iostream>
#include <vector>
#include "Map.h"
#include "LoggingObserver.h"

using namespace std;

// Forward declaration
class OrdersList;

class Order: public Subject, public ILoggable
{
public:
    virtual ostream& printOrder(ostream& output) const = 0;
    virtual bool validate() const = 0;
    virtual void execute() = 0;
    virtual Order* copy() const = 0;
    virtual ~Order() = default;

private:
    friend ostream& operator << (ostream& output, Order& o);
};

class OrdersList: public Subject, public ILoggable
{
public:
    OrdersList( );
    OrdersList(const OrdersList& o);
    void addOrder(Order* order);
    void removeOrder(int index);
    void moveOrderUp(int index);
    void moveOrderDown(int index);
    int getSize();
    string stringToLog() override;
    ostream& printList(ostream& output);
    Order* getOrder(int index);
    vector<Order*> getOrdersList();
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
    Deploy(Player* currentPlayer, int numOfArmies, Territory* targetTerritory);
    ostream& printOrder(ostream& output) const override;
    void execute() override;
    bool validate() const override;
    string stringToLog() override;
    Deploy* copy() const  override;
    Deploy& operator = (const Deploy& d);
    ~Deploy() override;

private:
    Player* currentPlayer;
    int numOfArmies;
    Territory* targetTerritory;
};

class Advance: public Order
{
public:
    Advance( );
    Advance(const Advance& a);
    Advance(Player* currentPlayer, int numOfArmies, Territory* sourceTerritory, Territory* targetTerritory);
    ostream& printOrder(ostream& output) const override;
    void execute() override;
    bool validate() const override;
    void attackSimulation() const;
    string stringToLog() override;
    Advance* copy() const  override;
    Advance& operator = (const Advance& a);
    ~Advance() override;

private:
    Player* currentPlayer;
    int numOfArmies;
    Territory* sourceTerritory; //***** Has to be changed to Territory object ptr *****
    Territory* targetTerritory; //***** Has to be changed to Territory object ptr *****
};

class Bomb: public Order
{
public:
    Bomb( );
    Bomb(const Bomb& b);
    explicit Bomb(Player* currentPlayer, Territory* targetTerritory);
    ostream& printOrder(ostream& output) const override;
    void execute() override;
    bool validate() const override;
    string stringToLog() override;
    Bomb* copy() const  override;
    Bomb& operator = (const Bomb& b);
    ~Bomb() override;

private:
    Player* currentPlayer;
    Territory* targetTerritory; //***** Has to be changed to Territory object ptr *****

};

class Blockade: public Order
{
public:
    Blockade( );
    Blockade(const Blockade& b);
    explicit Blockade(Player* currentPlayer, Territory* targetTerritory);
    ostream& printOrder(ostream& output) const override;
    void execute() override;
    bool validate() const override;
    string stringToLog() override;
    Blockade* copy() const  override;
    Blockade& operator = (const Blockade& b);
    ~Blockade() override;

private:
    Player* currentPlayer;
    Territory* targetTerritory; //***** Has to be changed to Territory object ptr *****
};

class Airlift: public Order{
public:
    Airlift( );
    Airlift(const Airlift& b);
    Airlift(Player* currentPlayer, int numOfArmies, Territory* sourceTerritory, Territory* targetTerritory);
    ostream& printOrder(ostream& output) const override;
    void execute() override;
    bool validate() const override;
    string stringToLog() override;
    Airlift* copy() const  override;
    Airlift& operator = (const Airlift& a);
    ~Airlift() override;

private:
    Player* currentPlayer;
    int numOfArmies;
    Territory* sourceTerritory;
    Territory* targetTerritory;
};

class Negotiate: public Order {
public:
    Negotiate( );
    Negotiate(const Negotiate& b);
    explicit Negotiate(Player* currentPlayer, Player* targetPlayer);
    ostream& printOrder(ostream& output) const override;
    void execute() override;
    bool validate() const override;
    string stringToLog() override;
    Negotiate* copy() const  override;
    Negotiate& operator = (const Negotiate& n);
    ~Negotiate() override;

private:
    Player* currentPlayer;
    Player* targetPlayer;
};
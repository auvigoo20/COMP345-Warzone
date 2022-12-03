#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "Cards.h"
#include "Map.h"
#include "Orders.h"

using namespace std;

class Player {

public:
    Player();
    ~Player();
    Player(string name, Hand* hand, OrdersList* ordersList, int reinforcementPool);
    Player(string name);
    Player(const Player&);
    Player& operator=(const Player &p);

    vector<Territory*> getTerritories();
    Hand* getHand();
    OrdersList* getOrdersList();
    int getReinforcementPool();
    string getName();
    bool getEntitledToCard();
    vector<Player*> getAllyPlayerList();
    vector<Player*> getOpponentPlayerList();

    void setTerritories(vector<Territory*> territories);
    void setHand(Hand* hand);
    void setOrdersList(OrdersList* ordersList);
    void setName(string name);
    void setReinforcementPool(int reinforcementPool);
    void setEntitledToCard(bool entitledToCard);
    void setAllyPlayerList(vector<Player*> allyPlayerList);
    void setOpponentPlayerList(vector<Player*> opponentPlayerList);

    void addTerritory(Territory* t);
    void removeTerritory(Territory* t);
    void addAlly(Player* p);

    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    bool issueOrder(bool isDeployPhase);
    void addReinforcements(int reinforcements);
    bool isAdjacentTerritory(Territory* targetTerritory);
    bool isAlly(Player* targetPlayer);

private:
    friend ostream& operator<<(ostream&, const Player&);
    string name;
    vector<Territory*> ownedTerritories;
    Hand* hand;
    OrdersList* orderList;
    int reinforcementPool;
    vector<Player*> allyPlayerList;
    vector<Player*> opponentPlayerList;
    bool entitledToCard;
};

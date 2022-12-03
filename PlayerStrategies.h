#pragma once

#include "Map.h"
#include "Player.h"

class PlayerStrategy{
public:
    virtual vector<Territory*> toAttack() = 0;
    virtual vector<Territory*> toDefend() = 0;
    virtual bool issueOrder(bool isDeployPhase) = 0;
    virtual ~PlayerStrategy() = 0;

private:
    Player* player;

    virtual bool issueDeployOrder() = 0;
    virtual void issueAdvanceOrder() = 0;
    virtual void issueAirliftOrder(int cardIndex) = 0;
    virtual void issueBombOrder(int cardIndex) = 0;
    virtual void issueBlockadeOrder(int cardIndex) = 0;
    virtual void issueNegotiateOrder(int cardIndex)  = 0;
    virtual void issueReinforcementOrder(int cardIndex) = 0;

};

class NeutralPlayerStrategy: public PlayerStrategy {
public:
    NeutralPlayerStrategy();
    NeutralPlayerStrategy(Player* player);
    NeutralPlayerStrategy(const NeutralPlayerStrategy& s);
    ~NeutralPlayerStrategy() override;

    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    bool issueOrder(bool isDeployPhase) override;
    NeutralPlayerStrategy& operator=(const NeutralPlayerStrategy& s);

    void setPlayer(Player* player);
    Player* getPlayer();

private:
    friend ostream& operator<<(ostream& output, NeutralPlayerStrategy& s);
    Player* player;
};


class AggressivePlayerStrategy: public PlayerStrategy {
public:
    AggressivePlayerStrategy();
    AggressivePlayerStrategy(Player* player);
    AggressivePlayerStrategy(const AggressivePlayerStrategy& s);
    ~AggressivePlayerStrategy() override;

    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    bool issueOrder(bool isDeployPhase) override;
    AggressivePlayerStrategy& operator=(const AggressivePlayerStrategy& s);

    void setPlayer(Player* player);
    Player* getPlayer();

private:
    friend ostream& operator<<(ostream& output, AggressivePlayerStrategy& s);
    Player* player;
};

class BenevolentPlayerStrategy: public PlayerStrategy {
public:
    BenevolentPlayerStrategy();
    BenevolentPlayerStrategy(Player* player);
    BenevolentPlayerStrategy(const BenevolentPlayerStrategy& s);
    ~BenevolentPlayerStrategy() override;

    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    bool issueOrder(bool isDeployPhase) override;
    BenevolentPlayerStrategy& operator=(const BenevolentPlayerStrategy& s);

    void setPlayer(Player* player);
    Player* getPlayer();

private:
    friend ostream& operator<<(ostream& output, BenevolentPlayerStrategy& s);
    Player* player;
};

class HumanPlayerStrategy: public PlayerStrategy {
public:
    HumanPlayerStrategy();
    HumanPlayerStrategy(Player* player);
    HumanPlayerStrategy(const HumanPlayerStrategy& s);
    ~HumanPlayerStrategy() override;

    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    bool issueOrder(bool isDeployPhase) override;
    HumanPlayerStrategy& operator=(const HumanPlayerStrategy& s);

    void setPlayer(Player* player);
    Player* getPlayer();

private:
    Player* player;

    bool issueDeployOrder() override;
    void issueAdvanceOrder() override;
    void issueAirliftOrder(int index) override;
    void issueBombOrder(int index) override;
    void issueBlockadeOrder(int index) override;
    void issueNegotiateOrder(int index) override;
    void issueReinforcementOrder(int index) override;
    void getAvailableOptions();
    void getHelp();
    int validateChoice(const string& choice);
    Territory* chooseTerritory(vector<Territory*> territories);
    int chooseNumArmies(Territory* territory);
    friend ostream& operator<<(ostream& output, HumanPlayerStrategy& s);
};

class CheaterPlayerStrategy: public PlayerStrategy {
public:
    CheaterPlayerStrategy();
    CheaterPlayerStrategy(Player* player);
    CheaterPlayerStrategy(const CheaterPlayerStrategy& s);
    ~CheaterPlayerStrategy() override;

    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    bool issueOrder(bool isDeployPhase) override;
    CheaterPlayerStrategy& operator=(const CheaterPlayerStrategy& s);

    void setPlayer(Player* player);
    Player* getPlayer();

private:
    Player* player;
};

void printTerritoryVector(const vector<Territory*> v);
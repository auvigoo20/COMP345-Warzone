#pragma once

#include "Map.h"

class PlayerStrategy{
public:
    virtual vector<Territory*> toAttack() = 0;
    virtual vector<Territory*> toDefend() = 0;
    virtual bool issueOrder(bool isDeployPhase) = 0;
    virtual string getStrategyType() = 0;
    virtual ~PlayerStrategy() = default;

    virtual Player* getPlayer() = 0;
    virtual void setPlayer(Player* p) = 0;

private:
    Player* player;
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

    void setPlayer(Player* player) override;
    Player* getPlayer() override;
    string getStrategyType() override;

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

    void setPlayer(Player* player) override;
    Player* getPlayer() override;
    string getStrategyType() override;

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

    void setPlayer(Player* player) override;
    Player* getPlayer() override;
    string getStrategyType() override;

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

    void setPlayer(Player* player) override;
    Player* getPlayer() override;
    string getStrategyType() override;

private:
    Player* player;

    bool issueDeployOrder();
    void issueAdvanceOrder();
    void issueAirliftOrder(int index);
    void issueBombOrder(int index);
    void issueBlockadeOrder(int index);
    void issueNegotiateOrder(int index);
    void issueReinforcementOrder(int index);
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

    void setPlayer(Player* player) override;
    Player* getPlayer() override;
    string getStrategyType() override;

private:
    Player* player;

    bool issueDeployOrder();
};

void printTerritoryVector(const vector<Territory*>& v);


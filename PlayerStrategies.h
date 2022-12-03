#pragma once

#include "Map.h"
#include "Player.h"

class PlayerStrategies{
public:
    virtual vector<Territory*> toAttack() = 0;
    virtual vector<Territory*> toDefend() = 0;
    virtual bool issueOrder(bool isDeployPhase) = 0;

private:
    Player* player;
};

class NeutralPlayerStrategy: public PlayerStrategies {
public:
    NeutralPlayerStrategy();
    NeutralPlayerStrategy(Player* player);
    NeutralPlayerStrategy(const NeutralPlayerStrategy& s);
    ~NeutralPlayerStrategy();

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


class AggressivePlayerStrategy: public PlayerStrategies {
public:
    AggressivePlayerStrategy();
    AggressivePlayerStrategy(Player* player);
    AggressivePlayerStrategy(const AggressivePlayerStrategy& s);
    ~AggressivePlayerStrategy();

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

class BenevolentPlayerStrategy: public PlayerStrategies {
public:
    BenevolentPlayerStrategy();
    BenevolentPlayerStrategy(Player* player);
    BenevolentPlayerStrategy(const BenevolentPlayerStrategy& s);
    ~BenevolentPlayerStrategy();

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

class HumanPlayerStrategy: public PlayerStrategies {
public:
    HumanPlayerStrategy();
    HumanPlayerStrategy(Player* player);
    HumanPlayerStrategy(const HumanPlayerStrategy& s);
    ~HumanPlayerStrategy();

    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    bool issueOrder(bool isDeployPhase) override;
    HumanPlayerStrategy& operator=(const HumanPlayerStrategy& s);

    void setPlayer(Player* player);
    Player* getPlayer();

private:
    Player* player;

    bool issueDeployOrder();
    void issueAdvanceOrder();
    void getAvailableOptions();
    void getHelp();
    bool validateChoice(const string& choice);
    friend ostream& operator<<(ostream& output, HumanPlayerStrategy& s);
};

class CheaterPlayerStrategy: public PlayerStrategies {
public:
    CheaterPlayerStrategy();
    CheaterPlayerStrategy(Player* player);
    CheaterPlayerStrategy(const CheaterPlayerStrategy& s);
    ~CheaterPlayerStrategy();

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
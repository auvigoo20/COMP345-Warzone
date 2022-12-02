#pragma once

#include "Map.h"
#include "Player.h"

class PlayerStrategies{
public:
    virtual vector<Territory*> toAttack() = 0;
    virtual vector<Territory*> toDefend() = 0;
    virtual void issueOrder() = 0;

private:
    Player* player;
};

class NeutralPlayerStrategy: public PlayerStrategies {
public:
    NeutralPlayerStrategy();
    NeutralPlayerStrategy(Player* player);
    ~NeutralPlayerStrategy();

    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    void issueOrder() override;

    void setPlayer(Player* player);
    Player* getPlayer();

private:
    Player* player;
};


class AggressivePlayerStrategy: public PlayerStrategies {
public:
    AggressivePlayerStrategy();
    AggressivePlayerStrategy(Player* player);
    ~AggressivePlayerStrategy();

    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    void issueOrder() override;

    void setPlayer(Player* player);
    Player* getPlayer();

private:
    Player* player;
};

class BenevolentPlayerStrategy: public PlayerStrategies {
public:
    BenevolentPlayerStrategy();
    BenevolentPlayerStrategy(Player* player);
    ~BenevolentPlayerStrategy();

    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    void issueOrder() override;

    void setPlayer(Player* player);
    Player* getPlayer();

private:
    Player* player;
};

class HumanPlayerStrategy: public PlayerStrategies {
public:
    HumanPlayerStrategy();
    HumanPlayerStrategy(Player* player);
    ~HumanPlayerStrategy();

    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    void issueOrder() override;

    void setPlayer(Player* player);
    Player* getPlayer();

private:
    Player* player;
};

class CheaterPlayerStrategy: public PlayerStrategies {
public:
    CheaterPlayerStrategy();
    CheaterPlayerStrategy(Player* player);
    ~CheaterPlayerStrategy();

    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
    void issueOrder() override;

    void setPlayer(Player* player);
    Player* getPlayer();

private:
    Player* player;
};

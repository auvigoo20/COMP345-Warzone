#include <list>;
int testing();

class Deck{
public:
    list<Card> deckList;



};

class Card{


};

class Bomb : Card{
public:
    int targetTerritory; //need to change for a node type

    Bomb();
    play(int targetTerritory);
};

class Reinforcement : Card{
public:
    int armyUnits;

    Reinforcement();
};

class Blockage : Card{
public:
    int targetTerritory;  //need to change for a node type

    Blockage();
 };

class Airlift : Card{
public:
    int armyUnits;
    int sourceTerritory;  //need to change for a node type
    int targetTerritory;  //need to change for a node type

    Airlift();
};

class Diplomacy : Card{
public:
    int targetPlayer;

    Diplomacy();
};
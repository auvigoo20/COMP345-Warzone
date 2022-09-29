#include <list>;
int testing();

class Deck{
public:
    list<Card> deckList;
};

class Hand{
    list<Card> playerHandList;
};

class Card{
};

class Bomb : Card{
public:
    Bomb();
    void play();
};

class Reinforcement : Card{
public:
    Reinforcement();
    void play();
};

class Blockage : Card{
public:
    Blockage();
    void play();
 };

class Airlift : Card{
public:
    Airlift();
    void play();
};

class Diplomacy : Card{
public:
    Diplomacy();
    void play();
};
#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int testing();
class Hand;
class Card;

class Deck{
public:
    Deck();
    Deck(const Deck& o);
    void addCard(Card* card);  //card being put back in the deck after play();
    void removeCard(int index); //random card is removed from deckList at draw();
    void draw(Hand* hand);
    vector<Card*> getDeckList();
    vector<Card*> deckList;
};

class Hand{
public:
    Hand();
    Hand(const Hand& o);
    void addCard(Card* card); //card is added in player's handList
    void removeCard(Card* card); //card is removed from hand to be played
    void playCard(Card* card);


private:
    vector<Card*> handList;
    Deck* deck;
};

class Card{
public:
    virtual void play() const = 0;
    Hand* handPlayer;
};

class Bomb : public Card{
public:
    Bomb();
    Bomb(const Bomb& b);
    void play();

};

class Reinforcement : public Card{
public:
    Reinforcement();
    Reinforcement(const Reinforcement& r);
    void play();

};

class Blockade : public Card{
public:
    Blockade();
    Blockade(const Blockade& bl);
    void play();

 };

class Airlift : public Card{
public:
    Airlift();
    Airlift(const Airlift& a);
    void play();

};

class Diplomacy : public Card{
public:
    Diplomacy();
    Diplomacy(const Diplomacy& d);
    void play();

};

#endif
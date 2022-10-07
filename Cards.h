#ifndef CARDS_H
#define CARDS_H
#pragma once
#include <iostream>
#include <vector>
#include "Orders.h"
#include "Player.h"

using namespace std;

int testCards();
class Hand;
class Card;

class Deck{
public:
    Deck();
    Deck(const Deck& o);
    void addCard(Card* card);
    void removeCard(int index);
    void draw(Hand* hand);            // Deck needs the Hand List of the player to add the draw card
    ostream& printDeck(ostream& output);
private:
    vector<Card*> deckList;
    friend ostream& operator << (ostream& output, Deck& d);
};

class Hand{
public:
    Hand();
    Hand(const Hand& o);
    Hand(Deck* deckList);       //Hand List needs the Deck list to place back the Card after play
    void addCard(Card* card);
    void removeCard(int index);
    void playCard(int index);
    ostream& printHand(ostream& output);
private:
    vector<Card*> handList;
    Deck* deckList;
    Player* owner;
    friend ostream& operator << (ostream& output, Hand& h);
};

class Card{
public:
    virtual void play(OrdersList* ordersList) const = 0; //Need to pass ordersList as a parameter because Cards have no access to it.
    virtual ostream& printCard(ostream& output) const = 0;
private:
    friend ostream& operator << (ostream& output, Card& c);
};

class BombCard : public Card{
public:
    BombCard();
    BombCard(const BombCard& b);
    void play(OrdersList* ordersList) const override;
    ostream& printCard(ostream& output) const override;
};

class ReinforcementCard : public Card{
public:
    ReinforcementCard();
    ReinforcementCard(const ReinforcementCard& r);
    void play(OrdersList* ordersList) const override;
    ostream& printCard(ostream& output) const override;
};

class BlockadeCard : public Card{
public:
    BlockadeCard();
    BlockadeCard(const BlockadeCard& bl);
    void play(OrdersList* ordersList) const override;
    ostream& printCard(ostream& output) const override;
 };

class AirliftCard : public Card{
public:
    AirliftCard();
    AirliftCard(const AirliftCard& a);
    void play(OrdersList* ordersList) const override;
    ostream& printCard(ostream& output) const override;
};

class DiplomacyCard : public Card{
public:
    DiplomacyCard();
    DiplomacyCard(const DiplomacyCard& d);
    void play(OrdersList* ordersList) const override;
    ostream& printCard(ostream& output) const override;
};

#endif

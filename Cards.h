#pragma once
#include <iostream>
#include <vector>
#include "Orders.h"

using namespace std;

class Hand;
class Card;

class Deck{
public:
    Deck();
    Deck(const Deck& o);
    void addCard(Card* card);
    void removeCard(int index);
    void draw(Hand* hand);            // Deck needs the Hand List of the player to add the draw card
    vector<Card*> getDeck();
    ostream& printDeck(ostream& output);
    Deck& operator = (const Deck& d);
    ~Deck();
private:
    vector<Card*> deckList;
    friend ostream& operator << (ostream& output, Deck& d);
};

class Hand{
public:
    Hand();
    Hand(const Hand& o);
    Hand(Player* owner, Deck* deckList);       //Hand List needs the Deck list to place back the Card after play
    void addCard(Card* card);
    void removeCard(int index);
    void playCard(int index);
    void setOwner(Player* owner);
    void setDeckList(Deck* deckList);
    vector<Card*>* getHandList();
    ostream& printHand(ostream& output);
    Hand& operator = (const Hand& h);
    ~Hand();
private:
    vector<Card*> handList;
    Deck* deckList;
    Player* owner;
    friend ostream& operator << (ostream& output, Hand& h);
};

class Card{
public:
    virtual ostream& printCard(ostream& output) const = 0;
    virtual Card* copy() const = 0;
    virtual ~Card() = default;
private:
    friend ostream& operator << (ostream& output, Card& c);
};

class BombCard : public Card{
public:
    BombCard();
    BombCard(const BombCard& b);
    void play(Player* owner, Territory* targetTerritory);
    ostream& printCard(ostream& output) const override;
    BombCard* copy() const override;
    ~BombCard() override;
};

class ReinforcementCard : public Card{
public:
    ReinforcementCard();
    ReinforcementCard(const ReinforcementCard& r);
    void play(Player* owner);
    ostream& printCard(ostream& output) const override;
    ReinforcementCard* copy() const override;
    ~ReinforcementCard() override;
};

class BlockadeCard : public Card{
public:
    BlockadeCard();
    BlockadeCard(const BlockadeCard& bl);
    void play(Player* owner, Territory* targetTerritory);
    ostream& printCard(ostream& output) const override;
    BlockadeCard* copy() const override;
    ~BlockadeCard() override;
 };

class AirliftCard : public Card{
public:
    AirliftCard();
    AirliftCard(const AirliftCard& a);
    void play(Player* owner, int numOfUnits, Territory* sourceTerritory, Territory* targetTerritory);
    ostream& printCard(ostream& output) const override;
    AirliftCard* copy() const override;
    ~AirliftCard() override;
};

class DiplomacyCard : public Card{
public:
    DiplomacyCard();
    DiplomacyCard(const DiplomacyCard& d);
    void play(Player* owner, Player* targetPlayer);
    ostream& printCard(ostream& output) const override;
    DiplomacyCard* copy() const override;
    ~DiplomacyCard() override;
};
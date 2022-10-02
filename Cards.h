#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <vector>

using namespace std;

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
    ostream& printDeck(ostream& output);
private:
    vector<Card*> deckList;
    friend ostream& operator << (ostream& output, Deck& d);
};

class Hand{
public:
    Hand();      //creates empty handList and empty pointer
    Hand(const Hand& o);
    Hand(Deck* deckList); //creates empty handList and pointer to existing deckList
    void addCard(Card* card); //card is added in player's handList
    void removeCard(int index); //card is removed from hand to be played
    void playCard(int index);
    ostream& printHand(ostream& output);
private:
    vector<Card*> handList;
    Deck* deckList;
    friend ostream& operator << (ostream& output, Hand& h);
};

class Card{
public:
    virtual void play() const = 0;
    virtual ostream& printCard(ostream& output) const = 0;
private:
    friend ostream& operator << (ostream& output, Card& c);
};

class Bomb : public Card{
public:
    Bomb();
    Bomb(const Bomb& b);
    void play() const override;
    ostream& printCard(ostream& output) const override;


};

class Reinforcement : public Card{
public:
    Reinforcement();
    Reinforcement(const Reinforcement& r);
    void play() const override;
    ostream& printCard(ostream& output) const override;
};

class Blockade : public Card{
public:
    Blockade();
    Blockade(const Blockade& bl);
    void play() const override;
    ostream& printCard(ostream& output) const override;
 };

class Airlift : public Card{
public:
    Airlift();
    Airlift(const Airlift& a);
    void play() const override;
    ostream& printCard(ostream& output) const override;
};

class Diplomacy : public Card{
public:
    Diplomacy();
    Diplomacy(const Diplomacy& d);
    void play() const override;
    ostream& printCard(ostream& output) const override;
};

#endif
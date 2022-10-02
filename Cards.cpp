#include "Cards.h"
#include "Map.h"
#include <iostream>

using std::cout;
using std::endl;

int testing(){
    return 123;
}

Deck::Deck(const Deck& o){
    this -> deckList = o.deckList;
}

void Deck::addCard(Card* card) {
    deckList.push_back(card);
}

void Deck::removeCard(int index) {
    deckList.erase(deckList.begin() + index);
}

vector<Card *> Deck::getDeckList() {
    return deckList;
}

void Deck::draw(Hand* hand) {
    int index = rand() % deckList.size();
    Card* cardDraw = deckList[index];
    removeCard(index);
    hand->addCard(cardDraw);
}

Hand::Hand(const Hand& o){
    this -> handList = o.handList;
}

void Hand::addCard(Card* card) {
    handList.push_back(card);

}
void Hand::removeCard(Card* card) {

}
void Hand::playCard(Card* card){
    card->play();
    removeCard(card);                //remove card from hand player
    deck->addCard(card);            // add card to deck
}

Bomb::Bomb(){
}
Reinforcement::Reinforcement() {
}
Blockade::Blockade() {
}
Airlift::Airlift() {
}
Diplomacy::Diplomacy() {
}

void Bomb::play(){
//create order bomb

}
void Reinforcement::play() {
//create order reinforcement
}
void Blockade::play() {
//create order blockade
}
void Airlift::play() {
//create order airlift
}
void Diplomacy::play() {
//create order negotiate
}


int main()
{
    cout << testing() << endl;
    cout << testing2();
}
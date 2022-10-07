#include "Cards.h"
#include "Map.h"
#include <iostream>

using namespace std;

Deck::Deck(){
}

Deck::Deck(const Deck& d){
    this -> deckList = d.deckList;
}

void Deck::addCard(Card* card) {
    deckList.push_back(card);

}

void Deck::removeCard(int index) {
    deckList.erase(deckList.begin() + index);  //from the index we remove the pointer object in the deck list
}

vector<Card*> Deck::getDeckList() {
    return deckList;
}

void Deck::draw(Hand* hand) {
    int index = rand() % deckList.size();
    Card* cardDraw = deckList[index];
    removeCard(index);
    hand->addCard(cardDraw);
}
ostream& Deck::printDeck(std::ostream &output) {
    output << "Number of Cards in Deck: " << deckList.size() << endl;
    output << "Current Deck: " << endl;
    for (Card* card: deckList){
        output << " - " << *card << endl;
    }
    return output;
}

ostream& operator <<(ostream& output, Deck& d){
    return d.printDeck(output);
}

Hand::Hand(){
}

Hand::Hand(const Hand& h){
    this -> handList = h.handList;
}

Hand::Hand(Deck* deckList) {
    this->deckList = deckList;
}

void Hand::addCard(Card* card) {
    handList.push_back(card);
}

void Hand::removeCard(int index) {
    handList.erase(handList.begin() + index-1);
}

void Hand::playCard(int index){
    Card* card = handList[index-1];
    card->play();                     //create order
    removeCard(index);               //remove card from hand player
    deckList->addCard(card);        // add card to deck
}
ostream& Hand::printHand(std::ostream &output) {
    output << "Number of Cards in Hand: " << handList.size() << endl;
    output << "Current Hand: " << endl;
    for (Card* card: handList){
        output << " - " << *card << endl;
    }
    return output;
}

ostream& operator <<(ostream& output, Hand& h){
    return h.printHand(output);
}

ostream& operator <<(ostream& output, Card& c){
    return c.printCard(output);
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

void Bomb::play() const{
    cout << "output bomb card" << endl;                  //create order bomb
}

ostream& Bomb::printCard(std::ostream &output) const {
    output << " Bomb Card " << endl;
    return output;
}

void Reinforcement::play() const{
    cout << "output reinforcement card" << endl; //create order reinforcement
}

ostream& Reinforcement::printCard(std::ostream &output) const {
    output << " Reinforcement Card " << endl;
    return output;
}

void Blockade::play() const{
    cout << "output blockade card" << endl;                    //create order blockade
}

ostream& Blockade::printCard(std::ostream &output) const {
    output << " Blockade Card " << endl;
    return output;
}

void Airlift::play() const{
    cout << "output airlift card" << endl;                   //create order airlift
}

ostream& Airlift::printCard(std::ostream &output) const {
    output << " Airlift Card " << endl;
    return output;
}
void Diplomacy::play() const{
    cout << "output diplomacy card" << endl;                  //create order negotiate
}

ostream& Diplomacy::printCard(std::ostream &output) const {
    output << " Diplomacy Card " << endl;
    return output;
}

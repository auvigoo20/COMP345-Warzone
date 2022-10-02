#include "Cards.h"
#include "Map.h"
#include <iostream>

using namespace std;

int testing(){
    return 123;
}

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
    output << "Number of Cards: " << deckList.size() << endl;
    output << "Current Deck: " << endl;
    for (Card* card: this->deckList){
        output << " - " << card;
    }
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
    handList.erase(handList.begin() + index);
}

void Hand::playCard(int index){
    Card* card = handList[index-1];
    card->play();                      //create order
    removeCard(index);                //remove card from hand player
    deckList->addCard(card);        // add card to deck
}
ostream& Hand::printHand(std::ostream &output) {
    output << "Number of Cards: " << handList.size() << endl;
    output << "Current Hand: " << endl;
    for (Card* card: this->handList){
        output << " - " << card;
    }
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
//create order bomb
}

ostream& Bomb::printCard(std::ostream &output) const {
    output << " Bomb Card " << endl;
}

void Reinforcement::play() const{
//create order reinforcement
}

ostream& Reinforcement::printCard(std::ostream &output) const {
    output << " Reinforcement Card " << endl;
}

void Blockade::play() const{
//create order blockade
}

ostream& Blockade::printCard(std::ostream &output) const {
    output << " Blockade Card " << endl;
}

void Airlift::play() const{
//create order airlift
}

ostream& Airlift::printCard(std::ostream &output) const {
    output << " Airlift Card " << endl;
}
void Diplomacy::play() const{
//create order negotiate
}

ostream& Diplomacy::printCard(std::ostream &output) const {
    output << " Diplomacy Card " << endl;
}


int main()
{
    cout << testing() << endl;
    cout << testing2();
}
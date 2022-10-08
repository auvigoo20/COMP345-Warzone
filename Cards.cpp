#include "Cards.h"
#include "Map.h"
#include "Player.h"
#include <iostream>

using namespace std;

Deck::Deck(){
}

Deck::Deck(const Deck& d){
    for (auto card: d.deckList) {
        this->deckList.push_back(card->copy());
    }
}

void Deck::addCard(Card* card) {
    deckList.push_back(card);

}

/**
 * Used in draw method
 * Remove the pointer Card in the Deck
 * @param index
 */

void Deck::removeCard(int index) {
    deckList.erase(deckList.begin() + index);  //from the index we remove the pointer object in the deck list
}

/**
 * Removes Card from Deck to add in player's Hand
 * @param hand
 */

void Deck::draw(Hand* hand) {

    // Initialize random seed to ensure randomness
    srand(time(NULL));
    int index = rand() % deckList.size() -1;
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

/**
 * Assignment operator for the deck class.
 * Performs deep copy of Deck object.
 */
 Deck& Deck::operator = (const Deck& d)
{
     if (this != &d) {
         for (auto card: d.deckList) {
             this->deckList.push_back(card->copy());
         }
         return *this;
     }
     return *this;
}

Hand::Hand(){
}

Hand::Hand(const Hand& h){
    this -> handList = h.handList;
    this -> owner = h.owner;
}

Hand::Hand(Deck* deckList) {
    this->deckList = deckList;
}

/**
 * Add Card draw in players Hand
 * @param card
 */

void Hand::addCard(Card* card) {
    handList.push_back(card);
}

/**
 * Used when player wants to play a Card
 * Card is removed from his Hands by removing the Card's pointer from Hand List
 * @param index
 */

void Hand::removeCard(int index) {
    handList.erase(handList.begin() + index-1);
}

/**
 * Card is played by giving its index
 * Card is then removed from the player's Hand
 * Card is placed back in the Deck after play
 * @param index
 */

void Hand::playCard(int index){
    Card* card = handList[index-1];
    card->play(this->owner->getOrdersList());                     //create order
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

void Hand::setOwner(Player* p) {
    this->owner = p;
}

ostream& operator <<(ostream& output, Hand& h){
    return h.printHand(output);
}

ostream& operator <<(ostream& output, Card& c){
    return c.printCard(output);
}

BombCard::BombCard(){
}

BombCard::BombCard(const BombCard& b)
{

}

ReinforcementCard::ReinforcementCard() {
}

BlockadeCard::BlockadeCard() {
}

AirliftCard::AirliftCard() {
}

DiplomacyCard::DiplomacyCard() {
}

/**
 * Creating Order and adding the order in the Order List
 */

void BombCard::play(OrdersList* ordersList) const{
    Bomb* bomb = new Bomb();
    ordersList->addOrder(bomb);
    cout << "output bomb card" << endl;
}

ostream& BombCard::printCard(std::ostream &output) const {
    output << " Bomb Card " << endl;
    return output;
}

/**
 * Creates a new Bombcard object. To assist
 * in creation of deep copies in list, taking advantage
 * of polymorphic capacities.
 */
 BombCard* BombCard::copy() const
 {
    return new BombCard();
 }

void ReinforcementCard::play(OrdersList* ordersList) const{  // Reinforcement Card does not create an order
    cout << "output reinforcement card" << endl;
}

ostream& ReinforcementCard::printCard(std::ostream &output) const {
    output << " Reinforcement Card " << endl;
    return output;
}

/**
 * Creates a new Reinforcmentcard object. To assist
 * in creation of deep copies in list, taking advantage
 * of polymorphic capacities.
 */
ReinforcementCard* ReinforcementCard::copy() const
{
    return new ReinforcementCard();
}

void BlockadeCard::play(OrdersList* ordersList) const{
    Blockade* blockade = new Blockade();
    ordersList->addOrder(blockade);
    cout << "output blockade card" << endl;
}

ostream& BlockadeCard::printCard(std::ostream &output) const {
    output << " Blockade Card " << endl;
    return output;
}

/**
 * Creates a new BlockadeCard object. To assist
 * in creation of deep copies in list, taking advantage
 * of polymorphic capacities.
 */
BlockadeCard* BlockadeCard::copy() const
{
    return new BlockadeCard();
}

void AirliftCard::play(OrdersList* ordersList) const{
    Airlift* airlift = new Airlift();
    ordersList->addOrder(airlift);
    cout << "output airlift card" << endl;
}

ostream& AirliftCard::printCard(std::ostream &output) const {
    output << " Airlift Card " << endl;
    return output;
}

/**
 * Creates a new Airliftcard object. To assist
 * in creation of deep copies in list, taking advantage
 * of polymorphic capacities.
 */
AirliftCard* AirliftCard::copy() const
{
    return new AirliftCard();
}

void DiplomacyCard::play(OrdersList* ordersList) const{
    Negotiate* negotiate = new Negotiate();
    ordersList->addOrder(negotiate);
    cout << "output diplomacy card" << endl;
}

ostream& DiplomacyCard::printCard(std::ostream &output) const {
    output << " Diplomacy Card " << endl;
    return output;
}
/**
 * Creates a new DiplomacyCard object. To assist
 * in creation of deep copies in list, taking advantage
 * of polymorphic capacities.
 */
DiplomacyCard* DiplomacyCard::copy() const
{
    return new DiplomacyCard();
}


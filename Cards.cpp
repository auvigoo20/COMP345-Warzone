#include "Cards.h"
#include "Map.h"
#include "Player.h"
#include "Orders.h"
#include <iostream>

using namespace std;

Deck::Deck(){
}

/**
 * Copy constructor for Deck class.
 * @param d
 */
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

    if (this->deckList.empty()) {
        cout << "Attempted to draw, but the deck is empty!" << endl;
    } else {
        // Initialize random seed to ensure randomness
        srand(time(NULL));
        int index = rand() % deckList.size();
        Card* cardDraw = deckList.at(index);
        removeCard(index);
        hand->addCard(cardDraw);
    }
}

vector<Card*> Deck::getDeck() {
    return this->deckList;
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

Deck::~Deck()
{
     for(auto card: deckList){
         delete card;
         card = nullptr;
     }
    //Swapping content to a non-instantiated vector will deallocate its memory.
    vector<Card*>().swap(this->deckList);
}

Hand::Hand(){
}

Hand::Hand(const Hand& h){
    this -> owner = h.owner;
    this -> deckList = new Deck(*(h.deckList));
    for (auto card: h.handList) {
        this->handList.push_back(card->copy());
    }
}

Hand::Hand(Player* owner, Deck* deckList) {
    this->deckList = deckList;
    this->owner = owner;
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
    handList.erase(handList.begin() + index);
}

/**
 * Card is played by giving its index
 * Card is then removed from the player's Hand
 * Card is placed back in the Deck after play
 * @param index
 */

void Hand::playCard(int index){
    Card* card = handList.at(index);
    removeCard(index);              //remove card from hand player
    deckList->addCard(card);        // add card to deck
}

vector<Card*>* Hand::getHandList()
{
    return &this->handList;
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

void Hand::setDeckList(Deck *deckList) {
    this->deckList = deckList;
}

/**
 * Assignment operator for hand class
 * @param h
 * @return
 */
Hand& Hand::operator=(const Hand &h)
{
    if (this != &h) {
       for(auto card: h.handList) {
           this->handList.push_back(card->copy());
       }
       return *this;
    }
    return *this;
}

Hand::~Hand()
{
    for(auto card: handList){
        this->deckList->addCard(card);
    }
    //Swapping content to a non-instantiated vector will deallocate its memory.
    vector<Card*>().swap(this->handList);
}

ostream& operator <<(ostream& output, Hand& h){
    return h.printHand(output);
}

ostream& operator <<(ostream& output, Card& c){
    return c.printCard(output);
}

BombCard::BombCard()
{
    cardType = "bomb";
}

/**
 * Copy constructor for BombCard. Empty for now
 * as class has no members to copy.
 * @param b
 */
BombCard::BombCard(const BombCard& b)
{
    cardType = "bomb";
}

ReinforcementCard::ReinforcementCard() {
    cardType = "reinforcement";
}

/**
 * Copy constructor for ReinforcmentCard. Empty for now
 * as class has no members to copy.
 * @param b
 */
ReinforcementCard::ReinforcementCard(const ReinforcementCard& r)
{
    cardType = "reinforcement";
}

BlockadeCard::BlockadeCard() {
    cardType = "blockade";
}

/**
 * Copy constructor for BlockadeCard. Empty for now
 * as class has no members to copy.
 * @param r
 */
BlockadeCard::BlockadeCard(const BlockadeCard& r)
{
    cardType = "blockade";
}

AirliftCard::AirliftCard()
{
    cardType = "airlift";
}

/**
 * Copy constructor for AirliftCard. Empty for now
 * as class has no members to copy.
 * @param a
 */
AirliftCard::AirliftCard(const AirliftCard& a)
{
    cardType = "airlift";
}

DiplomacyCard::DiplomacyCard()
{
    cardType = "negotiate";
}

/**
 * Copy constructor for DiplomacyCard. Empty for now
 * as class has no members to copy.
 * @param d
 */
DiplomacyCard::DiplomacyCard(const DiplomacyCard& d)
{
    cardType = "negotiate";
}

/**
 * Creating Order and adding the order in the Order List
 */

void BombCard::play(Player* owner, Territory* targetTerritory) {
    Bomb* bomb = new Bomb(owner, targetTerritory);
    owner->getOrdersList()->addOrder(bomb);
}

ostream& BombCard::printCard(std::ostream &output) const {
    output << " Bomb Card " << endl;
    return output;
}

string BombCard::getCardType()
{
    return cardType;
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

 BombCard::~BombCard()
 {
 }

void ReinforcementCard::play(Player* owner) {  // Reinforcement Card does not create an order
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


string ReinforcementCard::getCardType()
{
    return cardType;
}

ReinforcementCard::~ReinforcementCard()
{
}

void BlockadeCard::play(Player* owner, Territory* targetTerritory) {
    Blockade* blockade = new Blockade(owner, targetTerritory);
    owner->getOrdersList()->addOrder(blockade);
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

string BlockadeCard::getCardType()
{
    return cardType;
}

BlockadeCard::~BlockadeCard()
{
}

void AirliftCard::play(Player* owner, int numOfUnits, Territory* sourceTerritory, Territory* targetTerritory) {
    Airlift* airlift = new Airlift(owner, numOfUnits, sourceTerritory, targetTerritory);
    owner->getOrdersList()->addOrder(airlift);
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

string AirliftCard::getCardType()
{
    return cardType;
}

AirliftCard::~AirliftCard()
{
}

void DiplomacyCard::play(Player* owner, Player* targetPlayer) {
    Negotiate* negotiate = new Negotiate(owner, targetPlayer);
    owner->getOrdersList()->addOrder(negotiate);
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

string DiplomacyCard::getCardType()
{
    return cardType;
}

DiplomacyCard::~DiplomacyCard()
{
}


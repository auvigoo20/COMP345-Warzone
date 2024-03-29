#include "PlayerStrategies.h"
#include "Player.h"

#include <algorithm>
using std::find;

#include <string>
using std::stoi;

// Human Player Strategy

// Constructors



HumanPlayerStrategy::HumanPlayerStrategy()
{
    this->player = nullptr;
}


HumanPlayerStrategy::HumanPlayerStrategy(Player *player)
{
   this->player = player;
}

/**
 * Copy constructor
 * @param s Strategy to copy
 */
HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy &s)
{
    this->player = s.player;
}

// Destructor
HumanPlayerStrategy::~HumanPlayerStrategy()
{
}

ostream& operator<<(ostream& output, HumanPlayerStrategy& s)
{
    return output << "Human Player Strategy" << endl;
}


// Getters and setters

Player* HumanPlayerStrategy::getPlayer()
{
    return this->player;
}


void HumanPlayerStrategy::setPlayer(Player *player)
{
    this->player = player;
}

string HumanPlayerStrategy::getStrategyType()
{
    return "human";
}

/**
 * Returns a list of enemy territories adjacent to an
 * owned territory.
 * @return List of enemy territories to attack.
 */
vector<Territory*> HumanPlayerStrategy::toAttack()
{
     vector<Territory*> toAttack;

     for(auto* ownedTerritory: this->player->getTerritories()) {
         for (auto* adjacentTerritory: ownedTerritory->getAdjacentTerritories()) {
             if(adjacentTerritory->getOwner() != this->player &&
             find(toAttack.begin(), toAttack.end(), adjacentTerritory) == toAttack.end()) {
                 toAttack.push_back(adjacentTerritory);
             }
         }
     }
     return toAttack;
}

/**
 * Returns the list of owned territory (human player
 * can then chooses the territory among them).
 */
vector<Territory*> HumanPlayerStrategy::toDefend()
{
    return this->player->getTerritories();
}


bool HumanPlayerStrategy::issueOrder(bool isDeployPhase)
{
    if(isDeployPhase) {
        // Deploy phase
        // returns true when reinforcement pool == 0 (endPhase)
        return issueDeployOrder();
    } else {
        // Reaches this line if deploy phase is done.
        string choice;
        getAvailableOptions();
        while(true) {
            cout << "Enter your choice:";
            cin >> choice;
            int cardIndex = validateChoice(choice);
            if(cardIndex == -1){
                cout << "Invalid input ! Enter '-h' for help." << endl;
                continue;
            }
            else if (choice == "advance"){
                issueAdvanceOrder();
                return false;
            }
            else if (choice == "airlift") {
                issueAirliftOrder(cardIndex);
                return false;
            }
            else if (choice == "bomb") {
                issueBombOrder(cardIndex);
                return false;
            }
            else if (choice == "blockade") {
                issueBlockadeOrder(cardIndex);
                return false;
            }
            else if (choice == "negotiate") {
                issueNegotiateOrder(cardIndex);
                return false;
            }
            else if (choice == "reinforcement") {
                issueReinforcementOrder(cardIndex);
                return false;
            }
            else if (choice == "-l") {
                //Print the options for the user
               getAvailableOptions();
               continue;
            }
            else if (choice == "-h") {
                // Print help for user
               getHelp();
               continue;
            }
            else if (choice == "-q") {
                // Indicates that no more orders are to be issued (endPhase).
               return true;
            }
        }
    }
}

/**
 * Function that interacts with a human player to
 * issue a deploy order. Function issues an order and returns true if
 * more deploy order can be issued, false other wise.
 * @return bool true if more deploy order can be issued, false other wise.
 */
bool HumanPlayerStrategy::issueDeployOrder()
{
    //Verify if other deploy orders can be issued. If not return false.
    if(player->getReinforcementPool() == 0) {
        cout << "No units to deploy." << endl;
        return true;
    }

    cout << " --- Deploy Orders --- \n\n" << endl;
    cout << player->getReinforcementPool() << " units left to deploy." << endl;

    //Print owned territories for the player to see and make decision
    vector<Territory*> targetTerritoriesList = toDefend();
    cout << " --- Target territory selection ---" << endl;
    printTerritoryVector(targetTerritoriesList);
    Territory* targetTer = chooseTerritory(targetTerritoriesList);
    string numArmiesStr; // Number of armies to deploy in said territory
    int numArmies;

    while (true) {
        cout << "Please specify the number of units to deploy:";
        cin >> numArmiesStr;
        cout << endl;
        try {
            numArmies = stoi(numArmiesStr);
        }catch(const std::exception& e){
            numArmies = -1;
        }
        if (numArmies < 1 || numArmies > player->getReinforcementPool()) {
            cout << "The specified number of armies to deployed is not in the available range.";
            cout << "The number of armies must be between 1 and " << player->getReinforcementPool();
            cout << endl;
            continue;
        } else {
            break;
        }
    }
    //Issue deploy order
    Deploy *deployOrder = new Deploy(player, numArmies, targetTer);
    player->getOrdersList()->addOrder(deployOrder);
    player->setReinforcementPool(this->player->getReinforcementPool() - numArmies);
    targetTer->setTempNumOfArmies(targetTer->getTempNumOfArmies() + numArmies);
    cout << "Deploy order issued for player " << player->getName() << ".\n";
    cout  << numArmies << " units to be deployed on " << targetTer->getName() << "." << endl;

    return false;

}


/**
 * Function that interacts with human player to issue
 * advance order.
 */
void HumanPlayerStrategy::issueAdvanceOrder()
{
    cout << " --- Advance Order --- \n" << endl;
    string advanceTypeStr;
    int advanceType;
    while(true) {
        cout << "Do you wish to:\n";
        cout << "\t1 - Defend (move armies to a territory you own.\n";
        cout << "\t2 - Attack (move armies to an enemy territory." << endl;
        cout << "Choose option 1 or 2: ";
        cin >> advanceTypeStr;
        cout << endl;

        try {
            advanceType = stoi(advanceTypeStr);
        }catch(const std::exception& e){
            advanceType = -1;
        }
        if (advanceType != 1 && advanceType != 2) {
            cout << "Invalid input !" << endl;
            continue;
        }
        break;
    }
    if (advanceType == 1) {
        //Defensive advance order (to owned territory)
        //Print owned territories for the player to see and make a decision.
        vector<Territory*> territoryList = toDefend();
        cout << " --- Source territory selection ---" << endl;
        printTerritoryVector(territoryList);
        Territory *sourceTer = chooseTerritory(territoryList);
        int numArmies = chooseNumArmies(sourceTer);
        cout << " --- Target territory selection ---" << endl;
        Territory *targetTer = chooseTerritory(territoryList);

        // Create Order
        Advance* advanceOrder = new Advance(player, numArmies, sourceTer, targetTer);
        player->getOrdersList()->addOrder(advanceOrder);
        cout << "Advance order issued for player " << player->getName() << ". " << endl;
        cout << numArmies << " advanced from " << sourceTer->getName() << " to ";
        cout << targetTer->getName() << "." << endl;
        cout << "***" << endl;
    }
    else if (advanceType == 2) {
        //Offensive advance order (to enemy territory)
        vector<Territory*> sourceTerritoryList = toDefend();
        vector<Territory*> targetTerritoryList = toAttack();
        cout << " --- Source territory selection ---" << endl;
        printTerritoryVector(sourceTerritoryList);
        Territory *sourceTer = chooseTerritory(sourceTerritoryList);
        int numArmies = chooseNumArmies(sourceTer);
        cout << " --- Target territory selection ---" << endl;
        printTerritoryVector(targetTerritoryList);
        Territory *targetTer = chooseTerritory(targetTerritoryList);

        // Create Order
        Advance* advanceOrder = new Advance(player, numArmies, sourceTer, targetTer);
        player->getOrdersList()->addOrder(advanceOrder);
        cout << "Advance order issued for player " << player->getName() << endl;
        cout << numArmies << " to be advanced from " << sourceTer->getName() << " to ";
        cout << targetTer->getName() << "." << endl;
        cout << "***" << endl;
    }
}

/**
 * Function that interacts with human to play an
 * airlift card.
 */
void HumanPlayerStrategy::issueAirliftOrder(int cardIndex)
{
    cout << " --- Airlift Order --- " << endl;
    //Airlift order (to owned territory)
    //Print owned territories for the player to see and make a decision.
    vector<Territory*> territoryList = toDefend();
    cout << " --- Source territory selection ---" << endl;
    printTerritoryVector(territoryList);
    Territory *sourceTer = chooseTerritory(territoryList);
    int numArmies = chooseNumArmies(sourceTer);
    cout << " --- Target territory selection ---" << endl;
    Territory *targetTer = chooseTerritory(territoryList);

    // Remove the card from the handlist and add it back to the decklist
    player->getHand()->playCard(cardIndex);
    AirliftCard* currentCard = dynamic_cast<AirliftCard*>(player->getHand()->getHandList()->at(cardIndex));
    //Plays the card and issues the order.
    currentCard->play(player, numArmies, sourceTer, targetTer);
    cout << "Airlift order issued for player " << player->getName() << endl;
    cout << numArmies << " to be airlifted from " << sourceTer->getName() << " to ";
    cout << targetTer->getName() << "." << endl;
    cout << "***" << endl;
}

/**
 * Function that interacts with human to play a
 * bomb card.
 */
void HumanPlayerStrategy::issueBombOrder(int cardIndex)
{
    cout << " --- Bomb Order --- " << endl;
    //Bomb order
    //Print to attack territories for the player to see and make a decision.
    vector<Territory*> territoryList = toAttack();
    printTerritoryVector(territoryList);
    cout << " --- Target territory selection ---" << endl;
    Territory *targetTer = chooseTerritory(territoryList);

    // Remove the card from the handlist and add it back to the decklist
    player->getHand()->playCard(cardIndex);
    BombCard* currentCard = dynamic_cast<BombCard*>(player->getHand()->getHandList()->at(cardIndex));
    //Plays the card and issues the order.
    currentCard->play(player, targetTer);
    cout << "Bomb order issued for player " << player->getName() << endl;
    cout << "Bomb to be thrown at enemy territory " << targetTer->getName();
    cout << " owned by " << targetTer->getOwner()->getName() << "." << endl;
    cout << "***" << endl;
}

/**
 * Function that interacts with human to play a
 * blockade card.
 */
void HumanPlayerStrategy::issueBlockadeOrder(int cardIndex)
{
    cout << " --- Blockade Order --- " << endl;
    //Blockade order
    //Print to attack territories for the player to see and make a decision.
    vector<Territory*> territoryList = toDefend();
    printTerritoryVector(territoryList);
    cout << " --- Target territory selection ---" << endl;
    Territory *targetTer = chooseTerritory(territoryList);

    // Remove the card from the handlist and add it back to the decklist
    player->getHand()->playCard(cardIndex);
    BlockadeCard* currentCard = dynamic_cast<BlockadeCard*>(player->getHand()->getHandList()->at(cardIndex));
    //Plays the card and issues the order.
    currentCard->play(player, targetTer);
    cout << "Blockade order issued for player " << player->getName() << endl;
    cout << "Blockade to be effective on territory " << targetTer->getName() << endl;
    cout << "***" << endl;
}


/**
 * Function that interacts with human to play a
 * diplomacy card.
 */
void HumanPlayerStrategy::issueNegotiateOrder(int cardIndex)
{
    cout << " --- Negotiate Order --- " << endl;
    //Blockade order
    //Print to attack territories for the player to see and make a decision.
    int i = 1;
    string indexStr;
    int index;
    for (auto* p: player->getOpponentPlayerList()) {
        cout << i << " - " << p->getName() << endl;
        i++;
    }
    while(true) {
        cout << "Please specify the index corresponding to the targeted player: ";
        cin >> indexStr;
        cout << endl;

        try{
           index = stoi(indexStr);
        } catch( const std::exception& e){
           index = -1;
        }
        index--;
        if(index < 0 || index >= player->getOpponentPlayerList().size()){
            cout << "The specified index is out of range. Index must be between 1 and "
                 << player->getOpponentPlayerList().size() << " ! " << endl;
            continue;
        }
        break;
    }

    // Remove the card from the handlist and add it back to the decklist
    player->getHand()->playCard(cardIndex);
    Player* targetPlayer = player->getOpponentPlayerList().at(index);
    DiplomacyCard* currentCard = dynamic_cast<DiplomacyCard*>(player->getHand()->getHandList()->at(cardIndex));
    //Plays the card and issues the order.
    currentCard->play(player, targetPlayer);
    cout << "Diplomacy order issued for player " << player->getName() << endl;
    cout << "Negotiation order issued on " << targetPlayer->getName() << "." << endl;
    cout << "***" << endl;
}


void HumanPlayerStrategy::issueReinforcementOrder(int cardIndex)
{
    ReinforcementCard* currentCard = dynamic_cast<ReinforcementCard *>(player->getHand()->getHandList()->at(cardIndex));
    player->getHand()->playCard(cardIndex);
    currentCard->play(player);

    cout << "Reinforcement order issued for player " << player->getName() << endl;
    cout << "Player now has " << player->getReinforcementPool() << " available troops." << endl;
    cout << "***" << endl;
}

/**
 * Allows human player to select a territory from a list of
 * territory pointers and return said pointer.
 * @param territories
 * @return pointer to a territory
 */
Territory* HumanPlayerStrategy::chooseTerritory(vector<Territory *> territories)
{
    string indexStr;
    int index;
    while(true) {
        cout << "Please specify the index corresponding to the selected territory:";
        cin >> indexStr;
        cout << endl;

        try {
           index = stoi(indexStr);
        } catch(const std::exception& e) {
            index = 0;
        }
        index--;

        if (index< 0 || index>= territories.size()) {
            cout << "The specified index is out of range. Index must be between 1 and "
                 << territories.size() << " ! " << endl;
            continue;
        }
        break;
    }
    return territories.at(index);
}


/**
 * Allows for the player to select a number of armies to advance;
 * @param sourceTerritory Source territory
 * @return
 */
int HumanPlayerStrategy::chooseNumArmies(Territory *sourceTerritory)
{
    int numArmies;
    while(true) {
        cout << "Specify the number of armies:";
        cin >> numArmies;
        cout << endl;

        if(numArmies <= 0) {
            cout << "Invalid input !" << endl;
            continue;
        }
        break;
    }
    return numArmies;
}


/**
 * Helper method that prints the list of order options
 * available to the player.
 */
void HumanPlayerStrategy::getAvailableOptions()
{
    cout << "List of available plays: \n" << endl;
    cout << " -\tAdvance Order \n" << endl;
    if(!player->getHand()->getHandList()->empty()) {
        for(auto* card: *player->getHand()->getHandList()) {
            cout << " - " << *card << endl;
        }
    }
    cout << "Enter '-h' for help." << endl;
    cout << "Enter '-l' to list the available plays" << endl;
    cout << "Enter '-q' to stop issuing orders." << endl;
}

/**
 * Helper function that prints a help notice aimed
 * at helping the human player to enter a valid input
 * when asked to play next order.
 */
void HumanPlayerStrategy::getHelp()
{
    cout << " --- HELP --- " << endl;
    cout << "Enter 'advance' to issue an advance order" << endl;
    cout << "Enter 'airlift' to play an airlift card." << endl;
    cout << "Enter 'bomb' to play a bomb card." << endl;
    cout << "Enter 'blockade' to play a blockade card." << endl;
    cout << "Enter 'negotiate' to play a negotiate card." << endl;
    cout << "Enter 'reinforcement' to play a reinforcement card" << endl;
    cout << "Enter '-q' to stop issuing orders." << endl;
    cout << "* Only cards that are present in your hand can be played. Enter '-l' for the list of available plays." << endl;
}

/**
 * Verifies that the option entered by the user is valid.
 * @param choice string entered by the used.
 * @return true if string is valid, false otherwise.
 */
int HumanPlayerStrategy::validateChoice(const string& choice)
{
    vector<string> validChoices = {"airlift", "bomb", "blockade", "negotiate", "reinforcement"};
    int index = 0;
    if(choice == "advance" || choice == "-h" || choice == "-l" || choice == "-q") {
        return 0;
    } else {
        for(auto* card: *player->getHand()->getHandList()) {
            if(card->getCardType() == choice) {
               return index;
            }
            index++;
        }
    }
    return -1;
}

// Aggressive Player Strategy


// Constructors

AggressivePlayerStrategy::AggressivePlayerStrategy()
{
    this->player = nullptr;
}


AggressivePlayerStrategy::AggressivePlayerStrategy(Player *player)
{
    this->player = player;
}

/**
 * Copy constructor
 * @param s Strategy to copy
 */
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy &s)
{
    this->player = s.player;
}

// Destructor
AggressivePlayerStrategy::~AggressivePlayerStrategy()
{
}

ostream& operator<<(ostream& output, AggressivePlayerStrategy& s)
{
    output << "Aggressive Player Strategy" << endl;
    return output;
}

// Getters and setters

Player* AggressivePlayerStrategy::getPlayer()
{
    return this->player;
}


void AggressivePlayerStrategy::setPlayer(Player *player)
{
    this->player = player;
}

string AggressivePlayerStrategy::getStrategyType()
{
    return "aggressive";
}

/**
 * Method to get the list of territories an Aggressive player should attack
 * @return A list of territories to advance to
 */
vector<Territory*> AggressivePlayerStrategy::toAttack()
{
    vector<Territory*> toAttack;

    for(Territory* ownedTerritory: this->player->getTerritories()) {
        for (Territory* adjacentTerritory: ownedTerritory->getAdjacentTerritories()) {
            if (adjacentTerritory->getOwner() != this->player &&
                find(toAttack.begin(), toAttack.end(), adjacentTerritory) == toAttack.end()) {
                toAttack.push_back(adjacentTerritory);
            }
        }
    }
    return toAttack;
}

/**
 * Method to get the list of territories an Aggressive player should defend.
 * For an aggressive player this will only be their strongest.
 * @return The strongest country the player has
 */
vector<Territory*> AggressivePlayerStrategy::toDefend()
{
    // Find the territories adjacent to enemy territories
    vector<Territory*> adjacentToEnemy;
    for (Territory* t : this->player->getTerritories()) {
        for (Territory* adjacent : t->getAdjacentTerritories()) {
            if (adjacent->getOwner() != this->player) {
                adjacentToEnemy.push_back(t);
                break;
            }
        }
    }

    // Find the strongest territory
    Territory* strongest = adjacentToEnemy.front();
    for (Territory* t : adjacentToEnemy) {
        if (t->getNumOfArmies() > strongest->getNumOfArmies()) {
            strongest = t;
        }
    }

    // Return list containing just the strongest
    return vector<Territory*>({strongest});
}

bool AggressivePlayerStrategy::issueOrder(bool isDeployPhase)
{
    if (isDeployPhase) {
        // Deploy to the strongest territory
        Territory* strongest = toDefend().front();
        int numArmies = player->getReinforcementPool();
        Deploy* deployOrder = new Deploy (player, numArmies, strongest);

        player->getOrdersList()->addOrder(deployOrder);
        player->setReinforcementPool(player->getReinforcementPool() - numArmies);
        strongest->setTempNumOfArmies(strongest->getTempNumOfArmies() + numArmies);

        cout << "Deploy order issued for player " << player->getName() << endl;
        cout  << numArmies << " units to be deployed on " << strongest->getName() << "." << endl;
        cout << "***" << endl;

        // This is the only deploy order the aggressive player will make
        return true;
    }

    // Play a card if applicable
    else if (!player->getHand()->getHandList()->empty()) {
        Card *cardToPlay = player->getHand()->getHandList()->front();
        string cardType = cardToPlay->getCardType();

        // Bomb an arbitrary adjacent enemy territory
        if (cardType == "bomb") {
            Territory *toBomb = toAttack().front();
            player->getHand()->playCard(0);
            dynamic_cast<BombCard *>(cardToPlay)->play(player, toBomb);

            cout << "Bomb order issued for player " << player->getName() << endl;
            cout << "Bomb to be thrown at enemy territory " << toBomb->getName();
            cout << " owned by " << toBomb->getOwner()->getName() << "." << endl;
            cout << "***" << endl;
        }

        // Simply play a reinforcement card
        else if (cardType == "reinforcement") {
            player->getHand()->playCard(0);
            dynamic_cast<ReinforcementCard *>(cardToPlay)->play(player);

            cout << "Reinforcement order issued for player " << player->getName() << endl;
            cout << "Player now has " << player->getReinforcementPool() << " available troops." << endl;
            cout << "***" << endl;
        }

        // Use blockade on an arbitrary owned territory that isn't the strongest
        else if (cardType == "blockade") {
            for (Territory *t: player->getTerritories()) {
                if (t != toDefend().front()) {
                    player->getHand()->playCard(0);
                    dynamic_cast<BlockadeCard *>(cardToPlay)->play(player, t);

                    cout << "Blockade order issued for player " << player->getName() << endl;
                    cout << "Blockade to be effective on territory " << t->getName() << endl;
                    cout << "***" << endl;

                    // No need to go through any more territories once we use the card.
                    break;
                }
            }
        }

        else if (cardType == "airlift") {
            // Find a "stuck" territory (ie one that is not adjacent to any enemy territories)
            // and airlift its troops to our strongest
            Territory* strongest = toDefend().front();
            Territory* source = nullptr;

            for (Territory* t : player->getTerritories()) {
                source = t;

                // Check if the source territory has an adjacent enemy territory
                // If it does then don't use it as our source
                for (Territory* adj : t->getAdjacentTerritories()) {
                    if (adj->getOwner() != player) {
                        source = nullptr;
                        break;
                    }
                }

                // If our source territory isn't null anymore then we have found a suitable territory
                if (source != nullptr) {
                    break;
                }
            }

            // If source is still nullptr then no "stuck" territories were found; pick the second-strongest territory
            if (source == nullptr) {
                // Find the territories adjacent to enemy territories
                vector<Territory*> adjacentToEnemy;
                for (Territory* t : this->player->getTerritories()) {
                    for (Territory* adjacent : t->getAdjacentTerritories()) {
                        if (adjacent->getOwner() != this->player) {
                            adjacentToEnemy.push_back(t);
                            break;
                        }
                    }
                }

                // Find the second-strongest territory, to use as source
                source = adjacentToEnemy.front();
                for (Territory* t : adjacentToEnemy) {
                    if (t->getNumOfArmies() > source->getNumOfArmies() && t != strongest) {
                        source = t;
                    }
                }
            }

            int numArmies = source->getTempNumOfArmies();
            player->getHand()->playCard(0);
            dynamic_cast<AirliftCard *>(cardToPlay)->play(player, numArmies, source, strongest);

            cout << "Airlift order issued for player " << player->getName() << endl;
            cout << numArmies << " to be airlifted from " << source->getName() << " to ";
            cout << strongest->getName() << "." << endl;
            cout << "***" << endl;
        }

        // Negotiate with an arbitrary enemy player
        else if (cardType == "negotiate") {
            Player *toNegotiate = toAttack().back()->getOwner();
            player->getHand()->playCard(0);
            dynamic_cast<DiplomacyCard *>(cardToPlay)->play(player, toNegotiate);

            cout << "Diplomacy order issued for player " << player->getName() << ".\n";
            cout << "Negotiation order issued on " << toNegotiate->getName() << "." << endl;
            cout << "***" << endl;
        }
    }

    else {
        // Advance all units from the strongest territory to an adjacent enemy territory
        Territory* strongest = toDefend().front();
        for (Territory* t : strongest->getAdjacentTerritories()) {
            if (t->getOwner() != player) {
                int numArmies = strongest->getTempNumOfArmies();
                Advance* advanceOrder = new Advance(player, numArmies, strongest, t);
                player->getOrdersList()->addOrder(advanceOrder);

                cout << "Advance order issued for player " << player->getName() << "." << endl;
                cout << numArmies << " advanced from " << strongest->getName() << " to ";
                cout << t->getName() << "." << endl;
                cout << "***" << endl;

                // This is the only Advance order an aggressive player will make,
                // and will also be the last order an aggressive player makes as wel.
                return true;
            }
        }
    }

    // Continue issuing orders until the final order (the advance order) is issued.
    return false;
}


// Benevolent Player Strategy


BenevolentPlayerStrategy::BenevolentPlayerStrategy()
{
    this->player = nullptr;
}


BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *player)
{
    this->player = player;
}


/**
 * Copy constructor
 * @param s Strategy to copy
 */
BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy &s)
{
    this->player = s.player;
}

// Destructor
BenevolentPlayerStrategy::~BenevolentPlayerStrategy()
{
}

ostream& operator<<(ostream& output, BenevolentPlayerStrategy& s)
{
    output << "Benevolent Player Strategy" << endl;
    return output;
}

// Getters and setters

Player* BenevolentPlayerStrategy::getPlayer()
{
    return this->player;
}


void BenevolentPlayerStrategy::setPlayer(Player *player)
{
    this->player = player;
}

/**
 * Returns the weakest territory. Weakest territory is defined as the
 * territory with the least army units deployed on. If multiple territories with same
 * number of units, returns the first occurence in the list.
 * @return
 */
vector<Territory*> BenevolentPlayerStrategy::toDefend()
{
    // Find the weakest territory
    Territory* weakest = player->getTerritories().front();
    for (Territory* t : player->getTerritories()) {
        if (t->getTempNumOfArmies() < weakest->getTempNumOfArmies()) {
            weakest = t;
        }
    }

    // Return list containing just the strongest
    return vector<Territory*>({weakest});
}

vector<Territory*> BenevolentPlayerStrategy::toAttack()
{
    vector<Territory*> empty;
    return empty;
}

string BenevolentPlayerStrategy::getStrategyType()
{
    return "benevolent";
}

bool BenevolentPlayerStrategy::issueOrder(bool isDeployPhase)
{
    if(isDeployPhase) {

        // Only returns true if no more units to deploy (endPhase)
        if(player->getReinforcementPool() == 0) {
            return true;
        }

        Territory* weakest = toDefend().front();
        int numArmies = 1;

        Deploy* deployOrder = new Deploy(player, numArmies, weakest);
        player->getOrdersList()->addOrder(deployOrder);
        player->setReinforcementPool(player->getReinforcementPool() - numArmies);
        weakest->setTempNumOfArmies(weakest->getTempNumOfArmies() + numArmies);

        cout << "Deploy order issued for player " << player->getName() << endl;
        cout  << numArmies << " units to be deployed on " << weakest->getName() << "." << endl;
        return false;
    }
    // When deploy phase is done, player will only play cards that do not harm other players
    // Namely Airlift, blockade, negotiate, and reinforcement cards.
    else {

        // First we go through the cards to play check if one can be played and play it.
        int cardIndex = 0;

        for(auto* card: *player->getHand()->getHandList()) {
            //Airlift moves units from the strongest territory to weakest
            if(card->getCardType() == "airlift") {

                // We get the strongest territory
                Territory* strongest = player->getTerritories().front();
                for(auto* t: player->getTerritories()) {
                    if(t->getTempNumOfArmies() > strongest->getTempNumOfArmies()) {
                        strongest = t;
                    }
                }

                // We get the weakest territory
                Territory* weakest = toDefend().front();

                // We determine the number of units to airlift
                // First get the average number of units across both territories
                int averageNumArmies = (weakest->getTempNumOfArmies() + strongest->getTempNumOfArmies()) / 2;

                // The number of armies to move is the difference between the number of units on the weakest
                // territory and this average.
                int numArmies = averageNumArmies - weakest->getTempNumOfArmies();

                // Player airlift card
                player->getHand()->playCard(cardIndex);
                dynamic_cast<AirliftCard *>(card)->play(player, numArmies, strongest, weakest);

                cout << "Airlift order issued for player " << player->getName() << endl;
                cout << numArmies << " to be airlifted from " << strongest->getName() << " to ";
                cout << weakest->getName() << "." << endl;
                return false; // keep checking for other possible cards

            }
            else if(card->getCardType() == "blockade") {
                // Blockade will be played on the weakest territory that is adjacent to a
                // territory owned by an enemy player.
                vector<Territory*> adjacentToEnemy;
                for (Territory* t : this->player->getTerritories()) {
                    for (Territory* adjacent : t->getAdjacentTerritories()) {
                        if (adjacent->getOwner() != this->player) {
                            adjacentToEnemy.push_back(t);
                            break;
                        }
                    }
                }

                // Find the weakest territory
                Territory* weakest = adjacentToEnemy.front();
                for (Territory* t : adjacentToEnemy) {
                    if (t->getNumOfArmies() < weakest->getNumOfArmies()) {
                        weakest = t;
                    }
                }

                player->getHand()->playCard(cardIndex);
                dynamic_cast<BlockadeCard *>(card)->play(player, weakest);

                cout << "Blockade order issued for player " << player->getName() << endl;
                cout << "Blockade to be effective on territory " << weakest->getName() << endl;
                cout << "***" << endl;
                return false; // keep checking for other possible cards

            }
            else if(card->getCardType() == "negotiate") {
                // Negotiate order is issued on the player that owns a territory
                // adjacent to the current player's weakest territory that has borders
                // with territories that are owned by an enemy player.
                vector<Territory*> adjacentToEnemy;
                for (Territory* t : this->player->getTerritories()) {
                    for (Territory* adjacent : t->getAdjacentTerritories()) {
                        if (adjacent->getOwner() != this->player) {
                            adjacentToEnemy.push_back(t);
                            break;
                        }
                    }
                }

                // Find the weakest territory
                Territory* weakest = adjacentToEnemy.front();
                for (Territory* t : adjacentToEnemy) {
                    if (t->getNumOfArmies() < weakest->getNumOfArmies()) {
                        weakest = t;
                    }
                }

                // Now we have to get the strongest enemy territory adjacent to this one.
                vector<Territory*> enemyTerritory;
                for(auto* t: weakest->getAdjacentTerritories()) {
                    if(t->getOwner() != player) {
                        enemyTerritory.push_back(t);
                    }
                }

                Territory* strongestEnemy = enemyTerritory.front();
                for(auto* t: enemyTerritory) {
                    if(t->getTempNumOfArmies() > strongestEnemy->getTempNumOfArmies()) {
                        strongestEnemy = t;
                    }
                }
                player->getHand()->playCard(cardIndex);
                dynamic_cast<DiplomacyCard *>(card)->play(player, strongestEnemy->getOwner());

                cout << "Diplomacy order issued for player " << player->getName() << ".\n";
                cout << "Negotiation order issued on " << strongestEnemy->getOwner()->getName() << "." << endl;
                cout << "***" << endl;
                return false; // keep checking for other possible cards
            }
            else if(card->getCardType() == "reinforcement") {
                player->getHand()->playCard(cardIndex);
                dynamic_cast<ReinforcementCard *>(card)->play(player);

                cout << "Reinforcement order issued for player " << player->getName() << endl;
                cout << "Player now has " << player->getReinforcementPool() << " available troops." << endl;
                cout << "***" << endl;
                return false;
            }
            cardIndex++;
        }

        // At this point, no more cards can be played. Player has to play an advance order.

        // The advance order consists on moving units from the strongest
        // territory to the weakest territory having border with it.

        // We first get the player's strongest territory

        Territory* weakest = toDefend().front();

        // We look for the strongest adjacent territory.

        Territory* strongest = weakest;
        for(Territory* t: weakest->getAdjacentTerritories()) {
            if(t->getOwner() == player && t->getTempNumOfArmies() > strongest->getTempNumOfArmies()) {
                strongest = t;
            }
        }

        // We determine the number of units to advance
        // The number of units to advance corresponds to average of the difference between
        // the number of units on the strongest and weakest territories.
        int numArmies = (strongest->getTempNumOfArmies() - weakest->getTempNumOfArmies()) / 2;

        Advance* advanceOrder = new Advance(player, numArmies, strongest, weakest);
        player->getOrdersList()->addOrder(advanceOrder);

        cout << "Advance order issued for player " << player->getName() << "." << endl;
        cout << numArmies << " advanced from " << strongest->getName() << " to ";
        cout << weakest->getName() << "." << endl;
        cout << "***" << endl;

        return true;
    }
}

// Neutral Player Strategy


NeutralPlayerStrategy::NeutralPlayerStrategy()
{
    this->player = nullptr;
}


NeutralPlayerStrategy::NeutralPlayerStrategy(Player *player)
{
    this->player = player;
}


/**
 * Copy constructor
 * @param s Strategy to copy
 */
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy &s)
{
    this->player = s.player;
}

// Destructor
NeutralPlayerStrategy::~NeutralPlayerStrategy()
{
}

ostream& operator<<(ostream& output, NeutralPlayerStrategy& s)
{
    output << "Neutral Player Strategy" << endl;
    return output;
}

// Getters and setters

Player* NeutralPlayerStrategy::getPlayer()
{
    return this->player;
}


void NeutralPlayerStrategy::setPlayer(Player* p)
{
    this->player = p;
}

string NeutralPlayerStrategy::getStrategyType()
{
    return "neutral";
}


vector<Territory*> NeutralPlayerStrategy::toDefend()
{
    vector<Territory*> emptyVector;
    return emptyVector;
}

vector<Territory*> NeutralPlayerStrategy::toAttack()
{
    vector<Territory*> emptyVector;
    return emptyVector;
}

/**
 * Issue order returns true (endPhase) and ends the order issuing
 * phase without issuing any order.
 * @param isDeployPhase
 * @return
 */
bool NeutralPlayerStrategy::issueOrder(bool isDeployPhase)
{
    if(isDeployPhase) {
        cout << "No deploy orders issued for neutral player" << endl;
    } else {
        cout << "No orders issued for neutral player" << endl;
    }
    return true;
}


// Cheater Player Strategy

CheaterPlayerStrategy::CheaterPlayerStrategy()
{
    this->player = nullptr;
}


CheaterPlayerStrategy::CheaterPlayerStrategy(Player *player)
{
    this->player = player;
}


/**
 * Copy constructor
 * @param s Strategy to copy
 */
CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy &s)
{
    this->player = s.player;
}

// Destructor
CheaterPlayerStrategy::~CheaterPlayerStrategy()
{
}


ostream& operator<<(ostream& output, CheaterPlayerStrategy& s)
{
    output << "Cheater Player Strategy" << endl;
    return output;
}


// Getters and setters

Player* CheaterPlayerStrategy::getPlayer()
{
    return this->player;
}


void CheaterPlayerStrategy::setPlayer(Player *player)
{
    this->player = player;
}

string CheaterPlayerStrategy::getStrategyType()
{
    return "cheater";
}

vector<Territory*> CheaterPlayerStrategy::toDefend()
{
    return player->getTerritories();
}

vector<Territory*> CheaterPlayerStrategy::toAttack()
{
    vector<Territory*> toAttack;

    for(auto* ownedTerritory: this->player->getTerritories()) {
        for (auto* adjacentTerritory: ownedTerritory->getAdjacentTerritories()) {
            if(adjacentTerritory->getOwner() != this->player &&
               find(toAttack.begin(), toAttack.end(), adjacentTerritory) == toAttack.end()) {
                toAttack.push_back(adjacentTerritory);
            }
        }
    }
    return toAttack;
}

bool CheaterPlayerStrategy::issueOrder(bool isDeployPhase)
{
    if(isDeployPhase) {
        return issueDeployOrder();
    }

   // Does not issue any other kind of orders but deploy orders.
   return true;
}

/**
 * Generates random parameters (number of armies and territory) and creates
 * deploy orders.
 * @return True if reinforcement pool is empty.
 */
bool CheaterPlayerStrategy::issueDeployOrder()
{
    //Verify if other deploy orders can be issued. If not return false.
    if(player->getReinforcementPool() == 0) {
        return true;
    }

    srand(time(NULL));
    int randomNumber = rand();
    //Generate random parameters for the deploy orders (No specific behavior specified).
    int randomIndex = randomNumber % (player->getTerritories().size() - 1);
    int numArmies = (randomNumber % player->getReinforcementPool()) + 1;
    Territory* targetTer = toDefend().at(randomIndex);

    Deploy* deployOrder = new Deploy(player, numArmies, targetTer);
    player->getOrdersList()->addOrder(deployOrder);
    player->setReinforcementPool(this->player->getReinforcementPool() - numArmies);
    targetTer->setTempNumOfArmies(targetTer->getTempNumOfArmies() + numArmies);
    cout << "Deploy order issued for player " << player->getName() << endl;
    cout  << numArmies << " units to be deployed on " << targetTer->getName() << "." << endl;
    cout << "***" << endl;

    return false;
}

/**
 * Given a vector of territories, prints them with an index.
 */
void printTerritoryVector(const vector<Territory*>& v) {
    int i = 1;
    for(auto* territory: v) {
        cout << i << " - " << territory->getName() << " - Available units: " << territory->getTempNumOfArmies() << endl;
        i++;
    }
}

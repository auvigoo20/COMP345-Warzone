#include "PlayerStrategies.h"

using std::find;
using std::tolower;

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

/**
 * Assignment Operator
 * @param s
 * @return
 */
HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy& s) {
    if(this != &s) {
        this->player = s.player;
    }
    return *this;
}

ostream& operator<<(ostream& output, HumanPlayerStrategy& s)
{
    output << "Human Player Strategy" << endl;
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
        return issueDeployOrder();
    } else {
        // Reaches this line if deploy phase is done.
        string choice;
        getAvailableOptions();
        while(true) {
            cout << "Enter your choice:";
            cin >> choice;
            if(!validateChoice(choice)){
                cout << "Invalid input ! Enter '-h' for help." << endl;
                continue;
            }
            else if (choice == "advance"){
                issueAdvanceOrder();
                return true;
            }
            else if (choice == "airlift") {

                return true;
            }
            else if (choice == "bomb") {

                return true;
            }
            else if (choice == "blockade") {

                return true;
            }
            else if (choice == "negotiate") {

                return true;
            }
            else if (choice == "reinforcement") {

                return true;
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
                // Indicates that no more orders are to be issued.
               return false;
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
    cout << " --- Deploy Orders --- \n\n" << endl;
    cout << player->getReinforcementPool() << " units left to deploy." << endl;

    //Print owned territories for the player to see and make decision
    vector<Territory*> targetTerritoriesList = toDefend();
    cout << " --- Target territory selection ---" << endl;
    printTerritoryVector(targetTerritoriesList);
    Territory* targetTer = chooseTerritory(targetTerritoriesList);
    int numArmies; // Number of armies to deploy in said territory

    while (true) {
        cout << "Please specify the number of units to deploy:";
        cin >> numArmies;
        cout << endl;
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
    cout << "Deploy order issued for player " << player->getName() << ". ";
    cout  << numArmies << "to be deployed on " << targetTer->getName() << "." << endl;

    //Verify if other deploy orders can be issued. If not return false.
    if(player->getReinforcementPool() == 0) {
        return true;
    } else {
        return false;
    }
}


/**
 * Function that interacts with human player to issue
 * advance order.
 */
void HumanPlayerStrategy::issueAdvanceOrder()
{
    cout << " --- Advance Order --- \n\n" << endl;
    int advanceType;
    while(true) {
        cout << "Do you wish to:\n";
        cout << "\t1 - Defend (move armies to a territory you own.\n";
        cout << "\t2 -  Attack (move armies to an enemy territory." << endl;
        cout << "Choose option 1 or 2: ";
        cin >> advanceType;
        cout << endl;

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
        cout << "Advance order issued for player " << player->getName() << ". ";
        cout << numArmies << " advanced from " << sourceTer->getName() << " to ";
        cout << targetTer->getName() << "." << endl;
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
        cout << "Advance order issued for player " << player->getName() << ". ";
        cout << numArmies << " advanced from " << sourceTer->getName() << " to ";
        cout << targetTer->getName() << "." << endl;
    }
}

/**
 * Allows human player to select a territory from a list of
 * territory pointers and return said pointer.
 * @param territories
 * @return pointer to a territory
 */
Territory* HumanPlayerStrategy::chooseTerritory(vector<Territory *> territories)
{
    int index;
    while(true) {
        cout << "Please specify the index corresponding to the selected territory";
        cin >> index;
        cout << endl;
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
        cout << "Specify the number of armies to advance (between 1 and ";
        cout << sourceTerritory->getNumOfArmies() << "). :";
        cin >> numArmies;
        cout << endl;

        if(numArmies <= 0 || numArmies > sourceTerritory->getNumOfArmies()) {
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
    cout << "List of available plays: " << endl;
    cout << " - Advance order." << endl;
    if(!player->getHand()->getHandList()->empty()) {
        for(auto* card: *player->getHand()->getHandList()) {
            cout << " - " << card << "." << endl;
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
bool HumanPlayerStrategy::validateChoice(const string& choice)
{
    vector<string> validChoices = {"airlift", "bomb", "blockade", "negotiate", "reinforcement"};
    if(choice == "advance" || choice == "-h" || choice == "-l" || choice == "-q") {
        return true;
    } else {
        for(auto* card: *player->getHand()->getHandList()) {
            if(card->getCardType() == choice) {
                return true;
            }
        }
    }
    return false;
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

/**
 * Assignment Operator
 * @param s
 * @return
 */
AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& s) {
    if(this != &s) {
        this->player = s.player;
    }
    return *this;
}

ostream& operator<<(ostream& output, AggressivePlayerStrategy& s)
{
    output << "Aggressive Player Strategy" << endl;
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

/**
 * Assignment Operator
 * @param s
 * @return
 */
BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& s) {
    if(this != &s) {
        this->player = s.player;
    }
    return *this;
}

ostream& operator<<(ostream& output, BenevolentPlayerStrategy& s)
{
    output << "Benevolent Player Strategy" << endl;
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

/**
 * Assignment Operator
 * @param s
 * @return
 */
NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& s) {
    if(this != &s) {
        this->player = s.player;
    }
    return *this;
}

ostream& operator<<(ostream& output, NeutralPlayerStrategy& s)
{
    output << "Neutral Player Strategy" << endl;
}

// Getters and setters

Player* NeutralPlayerStrategy::getPlayer()
{
    return this->player;
}


void NeutralPlayerStrategy::setPlayer(Player *player)
{
    this->player = player;
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

/**
 * Assignment Operator
 * @param s
 * @return
 */
CheaterPlayerStrategy& CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy& s) {
    if(this != &s) {
        this->player = s.player;
    }
    return *this;
}

ostream& operator<<(ostream& output, CheaterPlayerStrategy& s)
{
    output << "Cheater Player Strategy" << endl;
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

/**
 * Given a vector of territories, prints them with an index.
 */
void printTerritoryVector(const vector<Territory*>& v) {
    int i = 1;
    for(auto* territory: v) {
        cout << i << " - " << territory->getName() << " : " << territory->getNumOfArmies() << endl;
    }
}

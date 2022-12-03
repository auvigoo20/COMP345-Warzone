#include "GameEngine.h"
#include "Player.h"
#include "CommandProcessing.h"
#include "Map.h"
#include "Cards.h"

#include <string>
using std::string;

#include <sstream>

#include <iostream>
using std::cin;
using std::cout;
using std::ostream;
using std::endl;

#include <vector>
using std::vector;

#include <algorithm>
using std::find;

/**
 * Transition default constructor
 */
Transition::Transition() {
    name = nullptr;
    to = nullptr;
}

/**
 * Transition copy constructor
 * @param t Transition to copy
 */
Transition::Transition(const Transition &t) {
    name = t.name;
    to = t.to;
}

/**
 * Construct a named transition to a single state
 * @param name The name of the transition
 * @param to The state the transition points to
 */
Transition::Transition(string name, State *to) {
    this->name = name;
    // Since we want transitions to a particular state to point to the same State object, a shallow copy is used here.
    this->to = to;
}

/**
 * Getter for the "name" variable
 * @return name
 */
string Transition::getName() {
    return name;
}

/**
 * Getter for the "to" variable
 * @return to
 */
State *Transition::getTo() {
    return to;
}

/**
 * Setter for the "name" variable
 * @param name The new name for the transition
 */
void Transition::setName(string name) {
    this->name = name;
}

/**
 * Setter for the "to" variable
 * @param to The new state pointer for the transition
 */
void Transition::setTo(State *to) {
    this->to = to;
}

/**
 * Transition assignment operator
 * @param t The transition to be assigned
 */
Transition& Transition::operator=(const Transition& t) {
    this->name = t.name;

    // Since we want transitions to a particular state to point to the same State object, a shallow copy is used here.
    this->to = t.to;
    return *this;
}

/**
 * Transition stream insertion operator
 * @param strm
 * @param s
 * @return strm
 */
ostream& operator << (ostream &strm, const Transition &t){
    return strm << "TRANSITION: Name: " << t.name << ", Target State: " << t.to->getName();
}

/**
 * State default constructor
 */
State::State() {
    name = nullptr;
    transitions = {};
}

/**
 * State copy constructor
 * @param s The state to copy
 */
State::State(const State &s) {
    name = s.name;

    // Since we want transitions from a particular state to point to the same Transition objects, a shallow copy is used here.
    transitions = s.transitions;
}

/**
 * Construct a named State with no transitions
 * @param name The name of the state
 */
State::State(std::string name) {
    this->name = name;
    this->transitions = {};
}

/**
 * Construct a named State with a vector of given possible transitions away from the state
 * @param name The name of the state
 * @param transitions Vector of transitions away from the state
 */
State::State(std::string name, vector<Transition *> transitions) {
    this->name = name;
    this->transitions = transitions;
}

/**
 * Getter for the "name" variable
 * @return name
 */
string State::getName() {
    return name;
}

/**
 * Getter for the "transitions" variable
 * @return transitions
 */
vector<Transition *> State::getTransitions() {
    return transitions;
}

/**
 * Setter for the "name" variable
 * @param name The new name for the state
 */
void State::setName(std::string name) {
    this->name = name;
}

/**
 * Setter for the "transitions" variable
 * @param transitions The new transitions vector for the state
 */
void State::setTransitions(vector<Transition *> transitions) {
    this->transitions = transitions;
}

/**
 * State assignment operator
 * @param s The state to be assigned
 */
State& State::operator=(const State& s) {
    this->name = s.name;

    // Since we want transitions from a particular state to point to the same Transition objects, a shallow copy is used here.
    this->transitions = s.transitions;
    return *this;
}

/**
 * State stream insertion operator
 * @param strm
 * @param s
 * @return strm
 */
ostream& operator << (ostream &strm, const State &s){
    strm << "STATE: Name: " << s.name << ", Transitions: {";

    for (int i=0; i<s.transitions.size(); i++){
        strm << s.transitions.at(i)->getName();
        if (i < s.transitions.size()-1) {
            strm << ", ";
        }
    }
    return strm << "}";
}


/**
 * GameEngine default constructor
 */
GameEngine::GameEngine() {
    currentState = nullptr;
    players = {};
    map = nullptr;
    latestCommand = nullptr;
    initializeEngineStates();
    deck = new Deck();
}

/**
 * GameEngine copy constructor
 * @param g the GameEngine to copy
 */
GameEngine::GameEngine(const GameEngine &g) {
    // If multiple game engines share the same particular current state, we want them to point to the same State object.
    // Thus, a shallow copy is used here.
    currentState = g.currentState;
    latestCommand = g.latestCommand;
    for(auto player : g.players){
        players.push_back(player);
    }
    map = g.map;
    initializeEngineStates();
    deck = g.deck;
}

/**
 * Construct a GameEngine with a specified starting state
 * @param startingState The starting state of the GameEngine
 */
GameEngine::GameEngine(State *startingState) {
    currentState = startingState;
    latestCommand = nullptr;
    initializeEngineStates();
    deck = new Deck();
}

GameEngine::~GameEngine(){
    delete deck;
    deck = nullptr;
    delete map;
    map = nullptr;
    for (auto p : players){
        delete p;
        p = nullptr;
    }
}

GameEngine::GameEngine(State *startingState, vector<Player *> players, Map *map) {
    this->currentState = startingState;
    this->players = players;
    this->map = map;
}

string GameEngine::stringToLog() {
    return "Game Engine New State: " + this->currentState->getName();
}

/**
 * Getter for the "currentState" variable
 * @return currentState
 */
State *GameEngine::getCurrentState() {
    return currentState;
}

/**
 * Getter for the "latestCommand" variable
 * @return latestCommand
 */
Command* GameEngine::getLatestCommand() {
    return latestCommand;
}

/**
 * Getter for the "players" vector
 * @return players
 */
vector<Player*> GameEngine::getPlayers() {
    return players;
}

/**
 * Getter for the map variable
 * @return map
 */
Map* GameEngine::getMap() {
    return map;
}

/**
 * Getter for the command processor
 * @return commandProcessor
 */
CommandProcessor *GameEngine::getCommandProcessor() {
    return commandProcessor;
}

/**
 * Getter for the deck
 * @return
 */
Deck *GameEngine::getDeck() {
    return deck;
}

/**
 * Setter for the "currentState" variable
 * @param currentState
 */
void GameEngine::transition(State *currentState) {
    this->currentState = currentState;
    notify(this);
}

/**
 * Setter for the "latestCommand" variable
 * @param latestCommand
 */
void GameEngine::setLatestCommand(Command* latestCommand) {
    this->latestCommand = latestCommand;
}

/**
 * Setter for the players vector
 * @param players
 */
void GameEngine::setPlayers(vector<Player *> players) {
    this->players = players;
}

/**
 * Setter for the map variable
 * @param map
 */
void GameEngine::setMap(Map *map) {
    this->map = map;
}

/**
 * Setter for the command processor
 * @param commandProcessor
 */
void GameEngine::setCommandProcessor(CommandProcessor *commandProcessor) {
    this->commandProcessor = commandProcessor;
}

/**
 * Setter for the deck
 * @param deck
 */
void GameEngine::setDeck(Deck *deck) {
    this->deck = deck;
}

/**
 * GameEngine assignment operator
 * @param g The state to be assigned
 */
GameEngine& GameEngine::operator=(const GameEngine& g) {
    // If multiple game engines share the same particular current state, we want them to point to the same State object.
    // Thus, a shallow copy is used here.
    this->currentState = g.currentState;
    this->latestCommand = g.latestCommand;
    return *this;
}

/**
 * GameEngine stream insertion operator
 * @param strm
 * @param g
 * @return strm
 */
ostream& operator << (ostream &strm, const GameEngine &g){
    return strm << "GAME ENGINE: Current State: {" << *g.currentState << "}" << endl;
}


/**
 * These are all possible states of the GameEngine.
 * They are static because they are the "fixed" possible states any GameEngine can currently be in.
 * They are not const because these states need to be provided a vector of transitions to states; however the
 * transitions are not yet defined.
 */
State* GameEngine::start = new State("start");
State* GameEngine::mapLoaded = new State("map loaded");
State* GameEngine::mapValidated = new State("map validated");
State* GameEngine::playersAdded = new State("players added");
State* GameEngine::assignReinforcement = new State("assign reinforcement");
State* GameEngine::issueOrders = new State("issue orders");
State* GameEngine::executeOrders = new State("execute orders");
State* GameEngine::win = new State("win");

/**
 * These are all possible transitions to other states of the GameEngine.
 * Each transition can only point to one state.
 * They are static because they are the "fixed" possible transitions any GameEngine can currently be in.
 * They are not const because they depend on the States defined above.
 */
Transition* GameEngine::loadmapTransition = new Transition("loadmap", GameEngine::mapLoaded);
Transition* GameEngine::validatemapTransition = new Transition("validatemap", GameEngine::mapValidated);
Transition* GameEngine::addplayerTransition = new Transition("addplayer", GameEngine::playersAdded);
Transition* GameEngine::gamestartTransition = new Transition("gamestart", GameEngine::assignReinforcement);
Transition* GameEngine::issueorderTransition = new Transition("issueorder", GameEngine::issueOrders);
Transition* GameEngine::endissueordersTransition = new Transition("endissueorders", GameEngine::executeOrders);
Transition* GameEngine::execorderTransition = new Transition("execorder", GameEngine::executeOrders);
Transition* GameEngine::endexecordersTransition = new Transition("endexecorders", GameEngine::assignReinforcement);
Transition* GameEngine::winTransition = new Transition("win", GameEngine::win);
Transition* GameEngine::replayTransition = new Transition("replay", GameEngine::start);
// The 'end' Transition effectively finishes the GameEngine flow; thus it does not point to any other state.
Transition* GameEngine::quitTransition = new Transition("quit", nullptr);
Transition* GameEngine::tournamentTransition = new Transition("tournament", GameEngine::win);

/**
 * Initializes the states by providing them with the vector of possible transitions away from these states.
 * This is static because it handles the "fixed" possible transitions away from any current state.
 */
void GameEngine::initializeEngineStates() {
    start->setTransitions({loadmapTransition, tournamentTransition});
    mapLoaded->setTransitions({loadmapTransition, validatemapTransition});
    mapValidated->setTransitions({addplayerTransition});
    playersAdded->setTransitions({addplayerTransition, gamestartTransition});
    assignReinforcement->setTransitions({issueorderTransition});
    issueOrders->setTransitions({issueorderTransition, endissueordersTransition});
    executeOrders->setTransitions({execorderTransition, endexecordersTransition, winTransition});
    win->setTransitions({replayTransition, quitTransition});
}

void GameEngine::prepareGame() {
    cout << "******* Players have been created ******" << endl;

    // Resetting each players' ally and opponent lists
    this->updatePlayersAllyAndOpponentLists();

    // Distributing territories evenly among players

    int territoryCount = this->map->getAllTerritories().size();
    vector<Territory *> tempTerritories = this->map->getAllTerritories();
    int currentPlayer;

    for (int i = 0; i < territoryCount; i++) {
        currentPlayer = i % players.size();
        tempTerritories[i]->setOwner(players[currentPlayer]);
        players[currentPlayer]->addTerritory(tempTerritories[i]);
    }

    cout << endl << "******** Territories Distributed *******" << endl;

    // Randomly generating a new playing order

    srand(time(NULL));

    for (int i = 0; i < (players.size() * 2); i++) {
        int shuffle = (rand() % players.size());
        players.emplace_back(players.at(shuffle));
        players.erase(players.begin() + shuffle, players.begin() + shuffle + 1);
    }

    cout << endl << "******* Playing Order Determined *******" << endl;

    // Assigning troops to each players' reinforcement pool

    for (int i = 0; i < players.size(); i++) {
        players[i]->setReinforcementPool(50);
    }

    cout << endl << "********* Army Units Dispatched ********" << endl;

    // Drawing Cards to each players' hands

    // Creating the Deck
    for (int i = 0; i < players.size(); i++) {
        this->deck->addCard(new BombCard);
        this->deck->addCard(new ReinforcementCard);
        this->deck->addCard(new BlockadeCard);
        this->deck->addCard(new AirliftCard);
        this->deck->addCard(new DiplomacyCard);
    }

    // Creating hands and drawing cards to them
    for (int i = 0; i < players.size(); i++) {
        Player *tempPlayer = players.at(i);
        Hand *hand = new Hand(tempPlayer, deck);
        deck->draw(hand);
        deck->draw(hand);
        tempPlayer->setHand(hand);
        tempPlayer = nullptr;
    }

    cout << endl << "************** Cards Drawn *************" << endl;

    this->transition(assignReinforcement);
}

void GameEngine::startupPhase() {
    cout << "****************************************" << endl;
    cout << "*       Initiating Startup Phase       *" << endl;
    cout << "****************************************" << endl;

    this->currentState = start;
    Command *currentCommand;
    string stateName, fileDirectory;
    bool done = false;

    while (!done) {

        // Receive the command from Console input using the getCommand()
        currentCommand = commandProcessor->getCommand();
        this->setLatestCommand(currentCommand);
        stateName = currentState->getName();
        MapLoader mapLoader;

        if (!commandProcessor->validate(currentCommand)) {
            cout << "Invalid Command." << endl;
            currentCommand->saveEffect("Invalid Command was entered. No change in state.");
        }
        else {
            if (currentCommand->getCommand().find("loadmap") != string::npos && (stateName == "start"
            || stateName == "map loaded")) {
                // Obtains file directory from the command
                std::stringstream commandToSplit(currentCommand->getCommand());
                string segment;
                vector<string> splitCommand;
                while (getline(commandToSplit, segment, ' ')) {
                    splitCommand.push_back(segment);
                }
                fileDirectory = splitCommand[1];

                // Loading the map using the MapLoader object and assign the map to the game engine
                cout << "************ Loading Map... ************" << endl;
                this->map = mapLoader.readMapFile(fileDirectory);

                // If map file exists, we change state to map loaded
                if (this->map != nullptr) {
                    cout << *this->map;
                    cout << "************** Map Loaded **************" << endl;
                    if (stateName == "start") {
                        this->transition(mapLoaded);
                        currentCommand->saveEffect("loadmap command executed. Map file was loaded. "
                                                   "State has changed from start to map loaded.");
                    }
                    else{
                        currentCommand->saveEffect("loadmap command executed. Map file was loaded. "
                                                   "No change in state.");
                    }
                }
                else {
                    cout <<"Please enter another map file directory." << endl;
                    currentCommand->saveEffect("loadmap command executed. Map file was not loaded. "
                                               "No change in state.");
                }
            }
            else if (currentCommand->getCommand() == "validatemap" && stateName == "map loaded") {
                // If the map that has been loaded is valid, we change state to map validated
                if (this->map->validate()) {
                    this->transition(mapValidated);
                    currentCommand->saveEffect("validatemap command executed. Map is Valid. State has changed "
                                               "from map loaded to map validated.");
                }
                else {
                    cout << "Please enter another map file directory" << endl;
                    currentCommand->saveEffect("validatemap command executed. Map is Invalid. "
                                               "No change in state.");
                }
            }
            else if (currentCommand->getCommand().find("addplayer") != string::npos && (stateName == "map validated"
            || stateName == "players added")) {
                if (players.size() < 6) {
                    // Obtaining the player name from the command to create player
                    std::stringstream commandToSplit(currentCommand->getCommand());
                    string segment;
                    vector<string> splitCommand;
                    while (getline(commandToSplit, segment, ' ')) {
                        splitCommand.push_back(segment);
                    }

                    Player *player = new Player(splitCommand[1]);
                    players.push_back(player);

                    if (stateName == "map validated") {
                        this->transition(playersAdded);
                        currentCommand->saveEffect("addplayer command executed. Player object created. State "
                                                   "has changed from map validated to players added.");
                    }
                    else {
                        currentCommand->saveEffect("addplayer command executed. Player object created. "
                                                   "No change in state.");
                    }
                    cout << "Player " << splitCommand[1] << " has been created" << endl;
                }
                else {
                    cout << "Maximum number of Players added. Please start the game." << endl;
                    currentCommand->saveEffect("addplayer command executed. Player object limit reached. No "
                                               "change in state.");
                }
            } else if (currentCommand->getCommand() == "gamestart" && currentState->getName() == "players added") {
                if (players.size() < 2) {
                    cout << "Cannot start game. At least 2 players are required." << endl;
                    currentCommand->saveEffect("gamestart command executed. Minimum number of player objects "
                                               "not present. No change in state.");
                } else {
                    done = true;
                    this->prepareGame();

                    currentCommand->saveEffect("gamestart command executed. Territories distributed. "
                                               "Playing Order Determined. Army Units Assigned. Hands Created "
                                               "with 2 Cards from Deck");
                }
            }
        }
    }
    cout << endl;
    for (int i = 0; i < players.size(); i++) {
        cout << *players[i] << endl;
    }

    cout << "****************************************" << endl;
    cout << "*        Startup Phase Complete        *" << endl;
    cout << "****************************************" << endl;
}
/**
 * Performs the reinforcement phase.
 * Loops through every player and adds the deserved number of reinforcement troops to their pool.
 */
void GameEngine::reinforcementPhase() {
    cout << endl << "********** Reinforcement Phase **********" << endl;

    // Provide the required reinforcements to all players
    // This includes the neutral player (who for now is treated/behaves like any other player)
    for (Player* player : this->players) {
        // Player receives at least three troops, or up to as many troops as 1/3 of the amount of territories owned
        int numTerritoriesOwned = player->getTerritories().size();
        int numReinforcementTroops = 3;

        if (numTerritoriesOwned/3 >= 3) {
            numReinforcementTroops = numTerritoriesOwned / 3;
        }

        cout << "Player " << player->getName() << " owns " << player->getTerritories().size() << " territories and receives " << numReinforcementTroops << " troops." << endl;

        // Player also receives bonus troops for owning all territories in a continent.
        // Loop through each continent, check if player owns all territories in it, and give bonus if so.
        for (Continent* continent : this->map->getAllContinents()) {
            bool ownsAllTerritories = true;
            for (Territory* territory : this->map->getAllTerritoriesByContinent(continent)) {
                // if any territory in continent is not in player's owned territories
                if (territory->getOwner() != player) {
                    ownsAllTerritories = false;
                    break;
                }
            }
            // Give bonus troops
            if (ownsAllTerritories) {
                numReinforcementTroops += continent->getBonus();
                cout << "Player " << player->getName() << " receives " << continent->getBonus() << " bonus troops from continent " << continent->getName() << ". (total: " << numReinforcementTroops << ")" << endl;
            }
        }

        player->addReinforcements(numReinforcementTroops);
    }
    this->transition(issueOrders);
}

void GameEngine::issueOrdersPhase() {
    cout << endl << "********** Issue Orders Phase **********" << endl;

    // issueOrder() will only complete once the player signifies that they don't have any more orders to issue
    // Thus just a simple forloop like this will ensure that every player issues orders and that every player has
    // signified that they are done issuing orders.
    // This includes the neutral player (who for now is treated/behaves like any other player)
    for (Player* player : this->players) {
        cout << "Player issuing order: " << player->getName() << "..." << endl;
        player->issueOrder();
        cout << "Done issuing orders for " << player->getName() << ". " << *player << endl;
    }

    this->transition(executeOrders);
}

void GameEngine::executeOrdersPhase() {
    cout << endl << "********** Execute Orders Phase **********" << endl;

    for (Player* player : this->players) {
        cout << "Player " << player->getName() << " has " << player->getTerritories().size() << " territories." << endl;
    }

    bool gameWon = false;

    // First do all deploy orders of all players
    // This includes the neutral player (who for now is treated/behaves like any other player)
    int playersWithoutOrders = 0;
    while (playersWithoutOrders < this->players.size()) {
        for (Player* player : this->players) {
            // If player still has orders, they may still have deploy orders.
            // Else, player is done executing deploy orders and we can move on to the next player.
            if (player->getOrdersList()->getSize() >= 1) {
                // If top order can still be casted to Deploy* then it is a deploy order to be executed.
                // Else, player is done executing deploy orders and we can move on to the next player.
                if (dynamic_cast<Deploy*>(player->getOrdersList()->getOrder(1)) != nullptr) {
                    cout << "Executing deploy order for " << player->getName() << endl;
                    player->getOrdersList()->getOrder(1)->execute();
                    player->getOrdersList()->removeOrder(1);
                    cout << "***" << endl;
                } else {
                    playersWithoutOrders++;
                }
            } else {
                playersWithoutOrders++;
            }
        }
    }

    // Now do the rest of the orders
    // Keep executing orders until all players have no more orders to execute
    playersWithoutOrders = 0;
    int nextPlayer = 0;
    while (playersWithoutOrders < this->players.size() && !gameWon) {
        // Loop through each player and execute the top order in their list
        // This includes the neutral player (who for now is treated/behaves like any other player)
        for (int i=nextPlayer; i < this->players.size(); i++) {
            Player* player = players.at(i);

            // If player does not have any orders to execute, increment the counter by 1
            // Else if the player has at lease 1 order, reset the counter to 0 and then execute the order.
            //
            // Resetting the counter is necessary as any player that had no orders will be checked again in the round-
            // robin and thus will increment again.
            // In other words, we keep checking every player until we're sure that no more players have orders left.
            if (player->getOrdersList()->getSize() >= 1) {
                cout << "Executing non-deploy order for " << player->getName() << endl;
                playersWithoutOrders = 0;
                player->getOrdersList()->getOrder(1)->execute();

                // After every order execution, eliminate any players that control no territories.
                vector<int>result = checkAndEliminatePlayers();

                cout << "Eliminated: {";
                for (int j : result) {
                    cout << j << ", ";
                }
                cout << "}" << endl;

                // If no players were eliminated, continue as normal
                if (result.empty()) {
                    nextPlayer = 0;
                }

                    // If a player has won the game, set the flag.
                else if (result.front() == -1) {
                    gameWon = true;
                    break;
                }

                    // If a player has eliminated, the loop needs to be broken as the player list has changed
                    // and we need to restart the loop from the player that "deserves" to go next.
                else {
                    // nextPlayer will be one above the current index by default
                    nextPlayer = i + 1;


                    // if the next player's index is more than we have players, then that means the next player was the one
                    // eliminated, so the actual next player is the 0th player.
                    if (nextPlayer >= this->players.size()) {
                        nextPlayer = 0;
                    }

                        // otherwise, the player eliminated was either the current player or a previous one. In either case, the
                        // next player's index will have also gone down by one.
                    else {
                        for (int j : result) {
                            if (j <= i) {
                                nextPlayer--;
                            }
                        }
                    }

                    // Break the loop and restart from nextPlayer
                    cout << "Restarting loop at index " << nextPlayer << " (current players: " << this->players.size() << ")" << endl;
                    cout << "***" << endl;
                    break;
                }

                cout << "***" << endl;

                // If player is entitled to a card, give it to them
                if (player->getEntitledToCard()) {
                    this->deck->draw(player->getHand());
                    player->setEntitledToCard(false);
                }
                player->getOrdersList()->removeOrder(1);
            } else {
                playersWithoutOrders++;
            }
        }
    }

    if (!gameWon) {
        // Reset every players' ally lists
        for (Player* player : this->players) {
            player->setAllyPlayerList({});
        }

        // Update players' opponent lists (in case an opponent was removed from the game)
        this->updatePlayersAllyAndOpponentLists();

        // Move to the assign reinforcement phase
        this->transition(assignReinforcement);
    } else {
        this->transition(win);
    }
}

void GameEngine::mainGameLoop() {
    cout << "****************************************" << endl;
    cout << "*      Initiating Main Game Loop       *" << endl;
    cout << "****************************************" << endl;

    turn = 1;

    while(true) {
        cout << endl << "********** Turn " << turn << " **********" << endl;
        if (this->currentState == assignReinforcement) {
            reinforcementPhase();
        }
        if (this->currentState == issueOrders) {
            issueOrdersPhase();
        }

        // FOR NOW
        // To demonstrate that during the loop, the game removes players that have no territories and declares win when
        // a player controls all territories, I manually perform the following actions:
        // - After every turn, each player will be given a (random) card.
        // - After the issueorder phase of turn 3, player 3 will have no territories
        // - After the issueorder phase of turn 4, player 1 will have all territories.
        //
        // This is for demonstration purposes and thus this code can/will be removed in part 3.
        for (Player *player: this->players) {
            this->deck->draw(player->getHand());
        }
        if (turn == 3) {
            for (Territory* territory : this->players.at(2)->getTerritories()) {
                territory->setOwner(this->players.at(0));
                this->players.at(0)->addTerritory(territory);
            }
            this->players.at(2)->setTerritories({});
            cout << "All " << this->players.at(2)->getName() << " territories forcefully transferred to " << this->players.at(0)->getName() << endl;
        }
        if (turn == 4) {
            for (Territory* territory : this->players.at(1)->getTerritories()) {
                territory->setOwner(this->players.at(0));
                this->players.at(0)->addTerritory(territory);
            }
            this->players.at(1)->setTerritories({});
            cout << "All " << this->players.at(1)->getName() << " territories forcefully transferred to " << this->players.at(0)->getName() << endl;
        }
        //
        // Game loop continues here.

        if (this->currentState == executeOrders) {
            executeOrdersPhase();
        }
        if (this->currentState == win) {
            break;
        }
        turn++;
    }

    // Get the command from the console on game win
    Command* command;
    while(true) {
        command = this->commandProcessor->getCommand();
        if (commandProcessor->validate(command)) {
            Player* winningPlayer = this->players.front();
            command->saveEffect("player" + winningPlayer->getName() + " has won");

            // Clean up memory on game end
            delete winningPlayer;
            winningPlayer = nullptr;
            delete this->map;
            map = nullptr;
            delete this->deck;
            deck = nullptr;

            break;
        }
    }

    // Re-start the game if command is replay
    if (command->getCommand() == "replay") {
        this->transition(start);
        command->saveEffect("Replay command executed. Game engine is now in start state.");
        this->startupPhase();
    }
}

void GameEngine::updatePlayersAllyAndOpponentLists() {
    for (Player* player : this->players) {
        // Create opponentPlayerList for each player which is the list of all players minus that player
        vector<Player*> opponentPlayerList = this->players;
        for (int i=0; i<opponentPlayerList.size(); i++) {
            if (opponentPlayerList.at(i) == player) {
                opponentPlayerList.erase(opponentPlayerList.begin()+i);
            }
        }

        // Set allyPlayerList to empty since the turn is over, and reset the opponentPlayerList
        player->setOpponentPlayerList(opponentPlayerList);
        player->setAllyPlayerList({});
    }
}

vector<int> GameEngine::checkAndEliminatePlayers() {
    vector<int> numEliminated = {};
    bool win = false;
    Player* winningPlayer;
    for (int i=0; i<this->getPlayers().size(); i++) {
        Player* player = players.at(i);

        // If player controls no territories, remove them from the game.
        // This includes the neutral player (who for now is treated/behaves like any other player)
        if (player->getTerritories().empty()) {
            cout << "Player " << player->getName() << " was eliminated." << endl;
            delete this->players.at(i);
            this->players.at(i) = nullptr;
            this->players.erase(this->players.begin()+i);
            numEliminated.push_back(i);
        }

        // If player controls all territories then declare win.
        // Neutral territories must therefore not exist; any neutral territories need to be conquered before a win
        // can be declared.
        if (player->getTerritories().size() == this->map->getAllTerritories().size()) {
            winningPlayer = player;
            win = true;
        }
    }

    if (win) {
        cout << "Player " << winningPlayer->getName() << " has won! Game over." << endl;
        return vector<int>{-1};
    } else {
        return numEliminated;
    }
}
//******************
//TOURNAMENT METHODS
//******************
vector<string> GameEngine::getTournamentMapFiles() {
    return tournamentMapFiles;
}

void GameEngine::addTournamentMapFile(std::string filename) {
    tournamentMapFiles.push_back(filename);
}

void GameEngine::setTournamentMapFiles(vector<std::string> tournamentMapFiles) {
    this->tournamentMapFiles.swap(tournamentMapFiles);
}

vector<string> GameEngine::getTournamentPlayerStrategies() {
    return tournamentPlayerStrategies;
}

void GameEngine::addTournamentPlayerStrategy(std::string strategy) {
    tournamentPlayerStrategies.push_back(strategy);
}

void GameEngine::setTournamentPlayerStrategies(vector<std::string> tournamentPlayerStrategies) {
    this->tournamentPlayerStrategies.swap(tournamentPlayerStrategies);
}

int GameEngine::getTournamentNumOfGames() {
    return tournamentNumOfGames;
}

void GameEngine::setTournamentNumOfGames(int numOfGames) {
    tournamentNumOfGames = numOfGames;
}

int GameEngine::getTournamentMaxNumOfTurns() {
    return tournamentMaxNumOfTurns;
}

void GameEngine::setTournamentMaxNumOfTurns(int numOfTurns) {
    tournamentMaxNumOfTurns = numOfTurns;
}

void GameEngine::tournamentStartupPhase(std::string currentMap) {
    cout << "************* Starting Game ************" << endl;

    // Receive the command from Console input using the getCommand()
    MapLoader mapLoader;

    // Loading the map using the MapLoader object and assign the map to the game engine
    cout << "************ Loading Map... ************" << endl;
    this->map = mapLoader.readMapFile(currentMap);

    // If map file does not exist, the map has to be skipped.
    if (this->map == nullptr) {
        cout <<"WARN: Map " << currentMap << "not found; skipping map." << endl;
        transition(start);
        return;
    }

    // If the map that has been loaded is invalid, the map has to be skipped.
    if (!this->map->validate()) {
        cout <<"WARN: Map " << currentMap << "validation unsuccessful; skipping map." << endl;
        transition(start);
        return;
    }

    prepareGame();
}

void GameEngine::runTournament() {
    vector<Player*> tournamentPlayers;
    vector<vector<int>> tournamentResults;

    // WILL NEED TO CHANGE TO USE ACTUAL PLAYER STRATEGIES
    for (string strategy : getTournamentPlayerStrategies()) {
        tournamentPlayers.push_back(new Player(strategy));
    }

    players = tournamentPlayers;

    // Loop through each map in M and play G games
    for (string currentMap : getTournamentMapFiles()) {
        vector<int> mapResults;

        // Play a game in G
        for (int gameNumber=0; gameNumber < getTournamentNumOfGames(); gameNumber++) {
            tournamentStartupPhase(currentMap);

            // Execute game loop
        }
    }
}

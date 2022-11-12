#include "GameEngine.h"
#include "CommandProcessing.h"
#include "Map.h"
#include "Player.h"
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
 * Setter for the "currentState" variable
 * @param currentState
 */
void GameEngine::setCurrentState(State *currentState) {
    this->currentState = currentState;
}

/**
 * Setter for the "latestCommand" variable
 * @param latestCommand
 */
void GameEngine::setLatestCommand(Command* latestCommand) {
    this->latestCommand = latestCommand;
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
    return strm << "GAME ENGINE: Current State: {" << *g.currentState << "}, Latest Command: " << g.latestCommand;
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

/**
 * Initializes the states by providing them with the vector of possible transitions away from these states.
 * This is static because it handles the "fixed" possible transitions away from any current state.
 */
void GameEngine::initializeEngineStates() {
    start->setTransitions({loadmapTransition});
    mapLoaded->setTransitions({loadmapTransition, validatemapTransition});
    mapValidated->setTransitions({addplayerTransition});
    playersAdded->setTransitions({addplayerTransition, gamestartTransition});
    assignReinforcement->setTransitions({issueorderTransition});
    issueOrders->setTransitions({issueorderTransition, endissueordersTransition});
    executeOrders->setTransitions({execorderTransition, endexecordersTransition, winTransition});
    win->setTransitions({replayTransition, quitTransition});
}

void GameEngine::startupPhase() {
    cout << "****************************************" << endl;
    cout << "*       Initiating Startup Phase       *" << endl;
    cout << "****************************************" << endl;

    this->currentState = start;
    Command* currentCommand;
    CommandProcessor* commandProcessor= new CommandProcessor(this);
    string stateName, fileDirectory;
    bool done = false;

    while(!done) {

        // Receive the command from Console input using the getCommand()
        currentCommand = commandProcessor->getCommand();
        this->setLatestCommand(currentCommand);
        stateName = currentState->getName();
        MapLoader mapLoader;

        // If the command is valid
        if (!commandProcessor->validate(currentCommand)){
            cout << "Invalid Command," << endl;
        }
        else {
            if (currentCommand->getCommand().find("loadmap") != string::npos && (stateName == "start" || stateName == "map loaded")){

                // To obtain file directory from the command
                std::stringstream commandToSplit(currentCommand->getCommand());
                string segment;
                vector<string> splitCommand;
                while (getline(commandToSplit, segment, ' ')) {
                    splitCommand.push_back(segment);
                }

                fileDirectory = splitCommand[1];

                cout << "Loading Map..." << endl;
                this->map = mapLoader.readMapFile(fileDirectory);
                if (this->map != nullptr){
                    cout << *this->map << endl;
                    if (stateName == "start"){
                        this->setCurrentState(mapLoaded);
                    }
                }
                else{
                    cout << "Please enter another file directory." << endl;
                }

            }
            else if(currentCommand->getCommand() == "validatemap" && stateName == "map loaded"){

                this->map->validate();
                this->setCurrentState(mapValidated);

            }
            else if(currentCommand->getCommand().find("addplayer") != string::npos && (stateName == "map validated" || stateName == "players added")){
                if (players.size() < 6) {

                    std::stringstream commandToSplit(currentCommand->getCommand());
                    string segment;
                    vector<string> splitCommand;
                    while (getline(commandToSplit, segment, ' ')) {
                        splitCommand.push_back(segment);
                    }

                    Player *player = new Player(splitCommand[1]);

                    players.push_back(player);

                    if (stateName == "map validated") {
                        this->setCurrentState(playersAdded);
                    }

                }
                else{
                    cout << "Maximum number of Players added. Please start the game." << endl;
                }
            }
            else if (currentCommand->getCommand() == "gamestart" && currentState->getName() == "players added"){
                if (players.size() < 2) {
                    cout << "Cannot start game. At least 2 players are required." << endl;
                }
                else {
                    done = true;

                    cout << "Distributing territories..." << endl;

                    int territoryCount = this->map->getAllTerritories().size();
                    vector<Territory*> tempTerritories = this->map->getAllTerritories();
                    int currentPlayer;
                    for (int i = 0; i < (territoryCount/players.size()); i++){
                        currentPlayer = i % players.size();
                        tempTerritories[i]->setOwner(players[currentPlayer]);
                        players[currentPlayer]->addTerritory(tempTerritories[i]);

                        }
                    }

                    cout << "Determining play order..." << endl;

                    srand(time(NULL));

                    for (int i=0; i < (players.size()*2); i++) {
                        int shuffle = (rand() % players.size());
                        players.emplace_back(players.at(shuffle));
                        players.erase(players.begin()+shuffle,players.begin()+shuffle+1);
                    }


                    cout << "Dispatching army units..." << endl;

                    for (int i = 0; i < players.size(); i++){
                        players[i]->setReinforcementPool(50);
                    }

                    cout << "Drawing Cards..." << endl;

                    // Creating Deck
                    for (int i = 0; i < players.size(); i++){
                        this->deck->addCard(new BombCard);
                        this->deck->addCard(new ReinforcementCard);
                        this->deck->addCard(new BlockadeCard);
                        this->deck->addCard(new AirliftCard);
                        this->deck->addCard(new DiplomacyCard);
                    }

                    for (int i=0; i<players.size(); i++) {
                        Player* tempPlayer = players.at(i);
                        Hand* hand = new Hand(tempPlayer,deck);
                        deck->draw(hand);
                        deck->draw(hand);
                        tempPlayer->setHand(hand);
                        tempPlayer= nullptr;
                    }
                }
            }
        }
    for (int i = 0; i < players.size(); i++){
        cout << endl << *players[i] <<;
    }

    cout << endl << "****************************************" << endl;
    cout << "*        Startup Phase Complete        *" << endl;
    cout << "****************************************" << endl;
}





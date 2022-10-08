#include "GameEngine.h"
#include <string>
using std::string;

#include <iostream>
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
 * @param t The Transition to copy
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
    this->to = to;
}

string Transition::getName() {
    return name;
}

State *Transition::getTo() {
    return to;
}

void Transition::setName(string name) {
    this->name = name;
}

void Transition::setTo(State *to) {
    this->to = to;
}

//  Stream Insertion Operator
ostream& operator << (ostream &strm, const Transition &t){
    return strm << "TRANSITION: Name: " << t.name << " - Transition State: " << t.to << endl;
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

string State::getName() {
    return name;
}

vector<Transition *> State::getTransitions() {
    return transitions;
}

void State::setName(std::string name) {
    this->name = name;
}

void State::setTransitions(vector<Transition *> transitions) {
    this->transitions = transitions;
}

//  Stream Insertion Operator
ostream& operator << (ostream &strm, const State &s){
    strm << "STATE: Name: " << s.name << " - Next States: {";
    for (auto i : s.transitions){
        strm << i << ", ";
    }
    strm << "}" << endl;
}


/**
 * Default GameEngine constructor
 */
GameEngine::GameEngine() {
    currentState = nullptr;
    initializeEngineStates();
}

/**
 * Copy GameEngine constructor
 * @param g the GameEngine to copy
 */
GameEngine::GameEngine(const GameEngine &g) {
    currentState = g.currentState;
    latestCommand = g.latestCommand;
    initializeEngineStates();
}

/**
 * Construct a GameEngine with a specified starting state
 * @param startingState The starting state of the GameEngine
 */
GameEngine::GameEngine(State *startingState) {
    currentState = startingState;
    initializeEngineStates();
}

State *GameEngine::getCurrentState() {
    return currentState;
}

void GameEngine::setCurrentState(State *currentState) {
    this->currentState = currentState;
}

//  Stream Insertion Operator
ostream& operator << (ostream &strm, const GameEngine &g){
    return strm << "GAME ENGINE: Current State: " << g.currentState << " - Latest Command: " << g.latestCommand << endl;
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
Transition* GameEngine::assigncountriesTransition = new Transition("assigncountries", GameEngine::assignReinforcement);
Transition* GameEngine::issueorderTransition = new Transition("issueorder", GameEngine::issueOrders);
Transition* GameEngine::endissueordersTransition = new Transition("endissueorders", GameEngine::executeOrders);
Transition* GameEngine::execorderTransition = new Transition("execorder", GameEngine::executeOrders);
Transition* GameEngine::endexecordersTransition = new Transition("endexecorders", GameEngine::assignReinforcement);
Transition* GameEngine::winTransition = new Transition("win", GameEngine::win);
Transition* GameEngine::playTransition = new Transition("play", GameEngine::start);
// The 'end' Transition effectively finishes the GameEngine flow; thus it does not point to any other state.
Transition* GameEngine::endTransition = new Transition("end", nullptr);

/**
 * Initializes the states by providing them with the vector of possible transitions away from these states.
 * This is static because it handles the "fixed" possible transitions away from any current state.
 */
void GameEngine::initializeEngineStates() {
    start->setTransitions({loadmapTransition});
    mapLoaded->setTransitions({loadmapTransition, validatemapTransition});
    mapValidated->setTransitions({addplayerTransition});
    playersAdded->setTransitions({addplayerTransition, assigncountriesTransition});
    assignReinforcement->setTransitions({issueorderTransition});
    issueOrders->setTransitions({issueorderTransition, endissueordersTransition});
    executeOrders->setTransitions({execorderTransition, endexecordersTransition, winTransition});
    win->setTransitions({playTransition, endTransition});
}

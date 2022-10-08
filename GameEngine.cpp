#include "GameEngine.h"
#include <string>
using std::string;

#include <iostream>
using std::ostream;
using std::endl;

#include <vector>
using std::vector;

Transition::Transition() {
    name = nullptr;
    to = nullptr;
}

Transition::Transition(const Transition &t) {
    name = t.name;
    to = t.to;
}

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

State::State() {
    name = nullptr;
}

State::State(const State &s) {
    name = s.name;
    transitions = s.transitions;
}

State::State(std::string name) {
    this->name = name;
}

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
    return strm << "STATE: Name: " << s.name << " - Next States: " << s.getTransitions() << endl;
}


GameEngine::GameEngine() {
    currentState = nullptr;
    initializeEngineStates();
}

GameEngine::GameEngine(const GameEngine &g) {
    currentState = g.currentState;
    latestCommand = g.latestCommand;
    initializeEngineStates();
}

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



// TODO: Check if everything here has potential memory leaks that need to be fixed.

State* GameEngine::start = new State("start");
State* GameEngine::mapLoaded = new State("map loaded");
State* GameEngine::mapValidated = new State("map validated");
State* GameEngine::playersAdded = new State("players added");
State* GameEngine::assignReinforcement = new State("assign reinforcement");
State* GameEngine::issueOrders = new State("issue orders");
State* GameEngine::executeOrders = new State("execute orders");
State* GameEngine::win = new State("win");

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
Transition* GameEngine::endTransition = new Transition("end", nullptr);

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

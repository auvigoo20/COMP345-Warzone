#include "GameEngine.h"
#include <string>
using std::string;

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

Transition::Transition(string *name, State *to) {
    this->name = name;
    this->to = to;
}

string *Transition::getName() {
    return name;
}

State *Transition::getTo() {
    return to;
}

void Transition::setName(std::string *name) {
    this->name = name;
}

void Transition::setTo(State *to) {
    this->to = to;
}

State::State() {
    name = nullptr;
    transitions = nullptr;
}

State::State(const State &s) {
    name = s.name;
    transitions = s.transitions;
}

State::State(std::string *name, vector<Transition *>* transitions) {
    this->name = name;
    this->transitions = transitions;
}

string *State::getName() {
    return name;
}

vector<Transition *>* State::getTransitions() {
    return transitions;
}

void State::setName(std::string *name) {
    this->name = name;
}

void State::setTransitions(vector<Transition *>* transitions) {
    this->transitions = transitions;
}

GameEngine::GameEngine() {
    currentState = nullptr;
    latestCommand = new string(); //Memory Leak
    initializeEngineStates();
}

GameEngine::GameEngine(const GameEngine &g) {
    currentState = g.currentState;
    latestCommand = g.latestCommand;
    initializeEngineStates();
}

GameEngine::GameEngine(State *startingState) {
    currentState = startingState;
    latestCommand = new string(); //Memory Leak
    initializeEngineStates();
}

State *GameEngine::getCurrentState() {
    return currentState;
}

void GameEngine::setCurrentState(State *currentState) {
    this->currentState = currentState;
}


State* GameEngine::start = new State(new string("start"), new vector<Transition*>()); // memory leak for str and vector
State* GameEngine::mapLoaded = new State(new string("map loaded"), new vector<Transition*>());
State* GameEngine::mapValidated = new State(new string("map validated"), new vector<Transition*>()); // memory leak for str and vector
State* GameEngine::playersAdded = new State(new string("players added"), new vector<Transition*>()); // memory leak for str and vector
State* GameEngine::assignReinforcement = new State(new string("assign reinforcement"), new vector<Transition*>()); // memory leak for str and vector
State* GameEngine::issueOrders = new State(new string("issue orders"), new vector<Transition*>()); // memory leak for str and vector
State* GameEngine::executeOrders = new State(new string("execute orders"), new vector<Transition*>()); // memory leak for str and vector
State* GameEngine::win = new State(new string("win"), new vector<Transition*>()); // memory leak for str and vector

Transition* GameEngine::loadmapTransition = new Transition(new string("loadmap"), GameEngine::mapLoaded);
Transition* GameEngine::validatemapTransition = new Transition(new string("validatemap"), GameEngine::mapValidated);
Transition* GameEngine::addplayerTransition = new Transition(new string("addplayer"), GameEngine::playersAdded);
Transition* GameEngine::assigncountriesTransition = new Transition(new string("assigncountries"), GameEngine::assignReinforcement);
Transition* GameEngine::issueorderTransition = new Transition(new string("issueorder"), GameEngine::issueOrders);
Transition* GameEngine::endissueordersTransition = new Transition(new string("endissueorders"), GameEngine::executeOrders);
Transition* GameEngine::execorderTransition = new Transition(new string("execorder"), GameEngine::executeOrders);
Transition* GameEngine::endexecordersTransition = new Transition(new string("endexecorders"), GameEngine::assignReinforcement);
Transition* GameEngine::winTransition = new Transition(new string("win"), GameEngine::win);
Transition* GameEngine::playTransition = new Transition(new string("play"), GameEngine::start);
Transition* GameEngine::endTransition = new Transition(new string("end"), nullptr);

void GameEngine::initializeEngineStates() {
    start->setTransitions(new vector<Transition*>({loadmapTransition}));
    mapLoaded->setTransitions(new vector<Transition*>({loadmapTransition, validatemapTransition}));
    mapValidated->setTransitions(new vector<Transition*>({addplayerTransition}));
    playersAdded->setTransitions(new vector<Transition*>({addplayerTransition, assigncountriesTransition}));
    assignReinforcement->setTransitions(new vector<Transition*>({issueorderTransition}));
    issueOrders->setTransitions(new vector<Transition*>({issueorderTransition, endissueordersTransition}));
    executeOrders->setTransitions(new vector<Transition*>({execorderTransition, endexecordersTransition, winTransition}));
    win->setTransitions(new vector<Transition*>({playTransition, endTransition}));
}




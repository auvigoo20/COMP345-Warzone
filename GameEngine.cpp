#include "GameEngine.h"

Transition::Transition() {
    name = nullptr;
    to = nullptr;
}

Transition::Transition(const Transition &t) {
    name = t.name;
    to = t.to;
}

Transition::Transition(std::string *name, State *to) {
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
}

State::State(const State &s) {
    name = s.name;
    transitions = s.transitions;
}

State::State(std::string *name, vector<Transition *> transitions) {
    this->name = name;
    this->transitions = transitions;
}

string *State::getName() {
    return name;
}

vector<Transition *> State::getTransitions() {
    return transitions;
}

void State::setName(std::string *name) {
    this->name = name;
}

void State::setTransitions(vector<Transition *> transitions) {
    this->transitions = transitions;
}

GameEngine::GameEngine() {
    currentState = nullptr;
    latestCommand = new string(); //Memory Leak
}

GameEngine::GameEngine(const GameEngine &g) {
    currentState = g.currentState;
    latestCommand = g.latestCommand;
}

GameEngine::GameEngine(State *startingState) {
    currentState = startingState;
    latestCommand = nullptr;
}

State *GameEngine::getCurrentState() {
    return currentState;
}

string *GameEngine::getLatestCommand() {
    return latestCommand;
}

void GameEngine::setCurrentState(State *currentState) {
    this->currentState = currentState;
}

void GameEngine::setLatestCommand(std::string *latestCommand) {
    this->latestCommand = latestCommand;
}

State* GameEngine::start = new State("start", )

void GameEngine::startGame() {

}
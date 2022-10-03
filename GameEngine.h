#pragma once

#include <string>
using std::string;

#include <vector>
using std::vector;

// Declared here (forward declaration) because Transition needs to know State exists.
class State;

class Transition {
private:
    string* name;
    State* to;
public:
    Transition();
    Transition(const Transition &t);
    Transition(string* name, State* to);

    string* getName();
    State* getTo();
    void setName(string* name);
    void setTo(State* to);
};

class State {
private:
    string* name;
    vector<Transition*> transitions;
public:
    State();
    State(const State &s);
    State(string* name, vector<Transition*> transitions);

    string* getName();
    vector<Transition*> getTransitions();
    void setName(string* name);
    void setTransitions(vector<Transition*> transitions);
};

class GameEngine {
private:
    State* currentState;
public:
    string* latestCommand;

    GameEngine();
    GameEngine(const GameEngine &g);
    GameEngine(State* startingState);

    State* getCurrentState();
    string* getLatestCommand();
    void setCurrentState(State* currentState);
    void setLatestCommand(string* latestCommand);

    static State* start;
    static State* mapLoaded;

    void startGame();
};

//State* start;
//State* mapLoaded;
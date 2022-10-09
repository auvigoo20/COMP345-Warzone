#pragma once

#include <string>
using std::string;

#include <iostream>
using std::ostream;

#include <vector>
using std::vector;

// Declared here (forward declaration) because Transition needs to know State exists.
class State;

class Transition {
private:
    friend ostream& operator << (ostream&, const Transition&);
    string name;
    State* to;
public:
    Transition();
    Transition(const Transition &t);
    Transition(string name, State* to);
    Transition& operator = (const Transition& t);

    string getName();
    State* getTo();
    void setName(string name);
    void setTo(State* to);
};

class State {
private:
    friend ostream& operator << (ostream&, const State&);
    string name;
    vector<Transition*> transitions;
public:
    State();
    State(const State &s);
    explicit State(string name);
    State(string name, vector<Transition*> transitions);
    State& operator = (const State& s);

    string getName();
    vector<Transition*> getTransitions();
    void setName(string name);
    void setTransitions(vector<Transition*> transitions);
};

class GameEngine {
private:
    friend ostream& operator << (ostream&, const GameEngine&);
    State* currentState;
    static void initializeEngineStates();
public:
    string latestCommand;

    GameEngine();
    GameEngine(const GameEngine &g);
    explicit GameEngine(State* startingState);
    GameEngine& operator = (const GameEngine& g);

    State* getCurrentState();
    void setCurrentState(State* currentState);

    // Since the States and Transitions will be the same for any/all GameEngines, they are made static.
    // However, since the States and Transition depend on each other, they cannot be made both const and static.
    static State* start;
    static State* mapLoaded;
    static State* mapValidated;
    static State* playersAdded;
    static State* assignReinforcement;
    static State* issueOrders;
    static State* executeOrders;
    static State* win;

    static Transition* loadmapTransition;
    static Transition* validatemapTransition;
    static Transition* addplayerTransition;
    static Transition* assigncountriesTransition;
    static Transition* issueorderTransition;
    static Transition* endissueordersTransition;
    static Transition* execorderTransition;
    static Transition* endexecordersTransition;
    static Transition* winTransition;
    static Transition* endTransition;
    static Transition* playTransition;
};
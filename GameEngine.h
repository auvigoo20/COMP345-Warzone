#pragma once

#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include <string>
using std::string;

#include <iostream>
using std::ostream;

#include <vector>
using std::vector;

// Forward declaration for Command in CommandProcessing.cpp
class Command;


// Declared here (forward declaration) because Transition needs to know State exists.
class State;
class CommandProcessor;

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

class GameEngine : public Subject, ILoggable {
private:
    State* currentState;
    vector<Player*> players;
    Map* map;
    CommandProcessor* commandProcessor;
    int turn;

    Command* latestCommand;
    Deck* deck;
    friend ostream& operator << (ostream&, const GameEngine&);
    static void initializeEngineStates();

    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase();

    //TOURNAMENT FIELDS
    vector<string> tournamentMapFiles;
    vector<string> tournamentPlayerStrategies;
    int tournamentNumOfGames;
    int tournamentMaxNumOfTurns;


public:
    GameEngine();
    GameEngine(const GameEngine &g);
    ~GameEngine();
    explicit GameEngine(State* startingState);
    explicit GameEngine(State* startingState, vector<Player*> players, Map* map);
    GameEngine& operator = (const GameEngine& g);

    State* getCurrentState();
    vector<Player*> getPlayers();
    Map* getMap();
    CommandProcessor* getCommandProcessor();
    Command* getLatestCommand();
    Deck* getDeck();

    void transition(State* currentState);
    void setPlayers(vector<Player*> players);
    void setMap(Map* map);
    void setCommandProcessor(CommandProcessor* commandProcessor);
    void setLatestCommand(Command* latestCommand);
    void setDeck(Deck* deck);

    void updatePlayersAllyAndOpponentLists();
    vector<int> checkAndEliminatePlayers();

    string stringToLog();

    void prepareGame();
    void startupPhase();
    void mainGameLoop();

    //TOURNAMENT METHODS
    vector<string> getTournamentMapFiles();
    void addTournamentMapFile(string filename);
    void setTournamentMapFiles(vector<string> tournamentMapFiles);
    vector<string> getTournamentPlayerStrategies();
    void addTournamentPlayerStrategy(string strategy);
    void setTournamentPlayerStrategies(vector<string> tournamentPlayerStrategies);
    int getTournamentNumOfGames();
    void setTournamentNumOfGames(int numOfGames);
    int getTournamentMaxNumOfTurns();
    void setTournamentMaxNumOfTurns(int numOfTurns);
    void tournamentStartupPhase(string currentMap);
    void runTournament();

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
    static Transition* gamestartTransition;
    static Transition* issueorderTransition;
    static Transition* endissueordersTransition;
    static Transition* execorderTransition;
    static Transition* endexecordersTransition;
    static Transition* winTransition;
    static Transition* quitTransition;
    static Transition* replayTransition;
    static Transition* tournamentTransition;
};
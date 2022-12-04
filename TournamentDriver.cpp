#include "TournamentDriver.h"
#include "GameEngine.h"
#include "CommandProcessing.h"
#include <iostream>
using std::cout;
using std::endl;

void testTournament(){

    // Setting up the game engine and command processor
    GameEngine* gameEngine = new GameEngine(GameEngine::start);
    CommandProcessor* commandProcessor = new CommandProcessor(gameEngine);
    gameEngine->setCommandProcessor(commandProcessor);
    commandProcessor->setGameEngine(gameEngine);

    //************************************************
    //THIS SECTION TESTS THE VALIDATION OF THE TOURNAMENT COMMAND IN THE COMMAND PROCESSOR
    //SOME EXAMPLE INPUTS:
    //INVALID:  tournament -M abc.txt def.txt ghi.txt -P cheater invalidStrategy -G 2 -D 15
    //INVALID:  tournament -M a.txt b.txt c.txt d.txt e.txt f.txt -P cheater aggressive -G 1 -D 10
    //VALID:    tournament -M abc.txt def.txt ghi.txt -P cheater aggressive -G 2 -D 15
    // tournament -M ../map_files/abc_valid.map ../map_files/canada_valid.map -P cheater aggressive benevolent -G 3 -D 15
    //************************************************
    Command* cmd = commandProcessor->getCommand();
    while(!commandProcessor->validate(cmd)){
        commandProcessor->validate(cmd);
        cout << *cmd;
        cmd = commandProcessor->getCommand();
    }
    cout << "\n\nDISPLAYING ALL COMMANDS:" << endl;
    cout << *commandProcessor;

    cout << "DISPLAYING GAME ENGINE TOURNAMENT'S ATTRIBUTES" << endl;
    cout << "Tournament maps: " << endl;
    for(auto map: gameEngine->getTournamentMapFiles()){
        cout << "\t" + map << endl;
    }
    cout << "Tournament player strategies: " << endl;
    for(auto strategy: gameEngine->getTournamentPlayerStrategies()){
        cout << "\t" + strategy << endl;
    }
    cout << "Tournament number of games:" << endl;
    cout <<  gameEngine->getTournamentNumOfGames() << endl;
    cout << "Tournament maximum number of turns" << endl;
    cout <<  gameEngine->getTournamentMaxNumOfTurns() << endl;

    cout << "Running tournament..." << endl;
    gameEngine->runTournament();

    delete gameEngine;
    delete commandProcessor;
    gameEngine = nullptr;
    commandProcessor = nullptr;
}

void testTournamentFile(string file){

    // Setting up the game engine and command processor
    GameEngine* gameEngine = new GameEngine(GameEngine::start);
    FileCommandProcessorAdapter* commandProcessor = new FileCommandProcessorAdapter(gameEngine, file);
    gameEngine->setCommandProcessor(commandProcessor);
    commandProcessor->setGameEngine(gameEngine);

    //************************************************
    //THIS SECTION TESTS THE VALIDATION OF THE TOURNAMENT COMMAND IN THE COMMAND PROCESSOR
    //SOME EXAMPLE INPUTS:
    //INVALID:  tournament -M abc.txt def.txt ghi.txt -P cheater invalidStrategy -G 2 -D 15
    //INVALID:  tournament -M a.txt b.txt c.txt d.txt e.txt f.txt -P cheater aggressive -G 1 -D 10
    //VALID:    tournament -M abc.txt def.txt ghi.txt -P cheater aggressive -G 2 -D 15
    // tournament -M ../map_files/abc_valid.map ../map_files/canada_valid.map -P cheater aggressive benevolent -G 3 -D 15
    //************************************************
    Command* cmd = commandProcessor->getCommand();
    while(!commandProcessor->validate(cmd)){
        commandProcessor->validate(cmd);
        cout << *cmd;
        cmd = commandProcessor->getCommand();
    }
    cout << "\n\nDISPLAYING ALL COMMANDS:" << endl;
    cout << *commandProcessor;

    cout << "DISPLAYING GAME ENGINE TOURNAMENT'S ATTRIBUTES" << endl;
    cout << "Tournament maps: " << endl;
    for(auto map: gameEngine->getTournamentMapFiles()){
        cout << "\t" + map << endl;
    }
    cout << "Tournament player strategies: " << endl;
    for(auto strategy: gameEngine->getTournamentPlayerStrategies()){
        cout << "\t" + strategy << endl;
    }
    cout << "Tournament number of games:" << endl;
    cout <<  gameEngine->getTournamentNumOfGames() << endl;
    cout << "Tournament maximum number of turns" << endl;
    cout <<  gameEngine->getTournamentMaxNumOfTurns() << endl;

    cout << "Running tournament..." << endl;
    gameEngine->runTournament();

    delete gameEngine;
    delete commandProcessor;
    gameEngine = nullptr;
    commandProcessor = nullptr;
}

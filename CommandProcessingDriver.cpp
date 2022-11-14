#include "CommandProcessingDriver.h"
#include "GameEngine.h"
#include "CommandProcessing.h"
#include <iostream>
using std::cout;
using std::endl;

void testCommandProcessor(){
    GameEngine* gameEngine = new GameEngine(GameEngine::start);
//    CommandProcessor* commandProcessor = new CommandProcessor(gameEngine);
//    FileCommandProcessorAdapter* commandProcessor = new FileCommandProcessorAdapter("../command_files/commands1.txt");
//    FileCommandProcessorAdapter* commandProcessor = new FileCommandProcessorAdapter("../command_files/commands2.txt");
    FileCommandProcessorAdapter* commandProcessor = new FileCommandProcessorAdapter("../command_files/commands3.txt");

    gameEngine->setCommandProcessor(commandProcessor);
    commandProcessor->setGameEngine(gameEngine);

    bool replay = true;

    while(replay){
        // Validate command in START state
        cout << *gameEngine;
        Command* cmd = commandProcessor->getCommand();
        commandProcessor->validate(cmd);

        while(!commandProcessor->validate(cmd)){
            commandProcessor->validate(cmd);
            cout << *cmd;
            cmd = commandProcessor->getCommand();
        }
        cmd->saveEffect("The map has been loaded.");
        cout << *cmd;


        // Validate command in MAP LOADED state
        gameEngine->transition(GameEngine::mapLoaded);
        cout << *gameEngine;
        cmd = commandProcessor->getCommand();
        commandProcessor->validate(cmd);

        while(!commandProcessor->validate(cmd) ||  cmd->getCommand() != "validatemap"){
            if(commandProcessor->validate(cmd) && cmd->getCommand() != "validatemap"){
                cmd->saveEffect("The map has been loaded.");
            }
            cout << *cmd;
            cmd = commandProcessor->getCommand();

        }
        cmd->saveEffect("The map has been validated");
        cout << *cmd;

        // Validate command in MAP VALIDATED state
        gameEngine->transition(GameEngine::mapValidated);
        cout << *gameEngine;
        cmd = commandProcessor->getCommand();
        commandProcessor->validate(cmd);

        while(!commandProcessor->validate(cmd)){
            commandProcessor->validate(cmd);
            cout << *cmd;
            cmd = commandProcessor->getCommand();
        }
        cmd->saveEffect("The player has been added.");
        cout << *cmd;

        // Validate command in PLAYERS ADDED state
        gameEngine->transition(GameEngine::playersAdded);
        cout << *gameEngine;
        cmd = commandProcessor->getCommand();
        commandProcessor->validate(cmd);

        while(!commandProcessor->validate(cmd) ||  cmd->getCommand() != "gamestart"){
            if(commandProcessor->validate(cmd) && cmd->getCommand() != "gamestart"){
                cmd->saveEffect("The player has been added.");
            }
            cout << *cmd;
            cmd = commandProcessor->getCommand();

        }
        cmd->saveEffect("The game has started");
        cout << *cmd;

        // Validate command in WIN state
        gameEngine->transition(GameEngine::win);
        cout << *gameEngine;
        cmd = commandProcessor->getCommand();
        commandProcessor->validate(cmd);

        while(!commandProcessor->validate(cmd)){
            commandProcessor->validate(cmd);
            cout << *cmd;
            cmd = commandProcessor->getCommand();
        }
        if(cmd->getCommand() == "quit"){
            replay = false;
            cmd->saveEffect("The game has ended.");
        }
        else{
            cmd->saveEffect("Replaying another game.");
            gameEngine->transition(GameEngine::start);

        }
        cout << *cmd;
    }

    cout << "\n\nDISPLAYING ALL COMMANDS:" << endl;
    cout << *commandProcessor;
    delete gameEngine;
    delete commandProcessor;
    gameEngine = nullptr;
    commandProcessor = nullptr;

}

void testCommandProcessorConsole(){
    cout << "INSIDE CONSOLE METHOD" << endl;
    GameEngine* gameEngine = new GameEngine(GameEngine::start);
    CommandProcessor* commandProcessor = new CommandProcessor(gameEngine);

   bool replay = true;

    while(replay){
        // Validate command in START state
        cout << *gameEngine;
        Command* cmd = commandProcessor->getCommand();
        commandProcessor->validate(cmd);

        while(!commandProcessor->validate(cmd)){
            commandProcessor->validate(cmd);
            cout << *cmd;
            cmd = commandProcessor->getCommand();
        }
        cmd->saveEffect("The map has been loaded.");
        cout << *cmd;


        // Validate command in MAP LOADED state
        gameEngine->transition(GameEngine::mapLoaded);
        cout << *gameEngine;
        cmd = commandProcessor->getCommand();
        commandProcessor->validate(cmd);

        while(!commandProcessor->validate(cmd) ||  cmd->getCommand() != "validatemap"){
            if(commandProcessor->validate(cmd) && cmd->getCommand() != "validatemap"){
                cmd->saveEffect("The map has been loaded.");
            }
            cout << *cmd;
            cmd = commandProcessor->getCommand();

        }
        cmd->saveEffect("The map has been validated");
        cout << *cmd;

        // Validate command in MAP VALIDATED state
        gameEngine->transition(GameEngine::mapValidated);
        cout << *gameEngine;
        cmd = commandProcessor->getCommand();
        commandProcessor->validate(cmd);

        while(!commandProcessor->validate(cmd)){
            commandProcessor->validate(cmd);
            cout << *cmd;
            cmd = commandProcessor->getCommand();
        }
        cmd->saveEffect("The player has been added.");
        cout << *cmd;

        // Validate command in PLAYERS ADDED state
        gameEngine->transition(GameEngine::playersAdded);
        cout << *gameEngine;
        cmd = commandProcessor->getCommand();
        commandProcessor->validate(cmd);

        while(!commandProcessor->validate(cmd) ||  cmd->getCommand() != "gamestart"){
            if(commandProcessor->validate(cmd) && cmd->getCommand() != "gamestart"){
                cmd->saveEffect("The player has been added.");
            }
            cout << *cmd;
            cmd = commandProcessor->getCommand();

        }
        cmd->saveEffect("The game has started");
        cout << *cmd;

        // Validate command in WIN state
        gameEngine->transition(GameEngine::win);
        cout << *gameEngine;
        cmd = commandProcessor->getCommand();
        commandProcessor->validate(cmd);

        while(!commandProcessor->validate(cmd)){
            commandProcessor->validate(cmd);
            cout << *cmd;
            cmd = commandProcessor->getCommand();
        }
        if(cmd->getCommand() == "quit"){
            replay = false;
            cmd->saveEffect("The game has ended.");
        }
        else{
            cmd->saveEffect("Replaying another game.");
            gameEngine->transition(GameEngine::start);

        }
        cout << *cmd;
    }

    cout << "\n\nDISPLAYING ALL COMMANDS:" << endl;
    cout << *commandProcessor;
    delete gameEngine;
    delete commandProcessor;
    gameEngine = nullptr;
    commandProcessor = nullptr;

}

void testCommandProcessorFile(string fileName){
    cout << "INSIDE FILE METHOD" << endl;
    GameEngine* gameEngine = new GameEngine(GameEngine::start);
    FileCommandProcessorAdapter* commandProcessor = new FileCommandProcessorAdapter(gameEngine, fileName);

    bool replay = true;

    while(replay){
        // Validate command in START state
        cout << *gameEngine;
        Command* cmd = commandProcessor->getCommand();
        commandProcessor->validate(cmd);

        while(!commandProcessor->validate(cmd)){
            commandProcessor->validate(cmd);
            cout << *cmd;
            cmd = commandProcessor->getCommand();
        }
        cmd->saveEffect("The map has been loaded.");
        cout << *cmd;


        // Validate command in MAP LOADED state
        gameEngine->transition(GameEngine::mapLoaded);
        cout << *gameEngine;
        cmd = commandProcessor->getCommand();
        commandProcessor->validate(cmd);

        while(!commandProcessor->validate(cmd) ||  cmd->getCommand() != "validatemap"){
            if(commandProcessor->validate(cmd) && cmd->getCommand() != "validatemap"){
                cmd->saveEffect("The map has been loaded.");
            }
            cout << *cmd;
            cmd = commandProcessor->getCommand();

        }
        cmd->saveEffect("The map has been validated");
        cout << *cmd;

        // Validate command in MAP VALIDATED state
        gameEngine->transition(GameEngine::mapValidated);
        cout << *gameEngine;
        cmd = commandProcessor->getCommand();
        commandProcessor->validate(cmd);

        while(!commandProcessor->validate(cmd)){
            commandProcessor->validate(cmd);
            cout << *cmd;
            cmd = commandProcessor->getCommand();
        }
        cmd->saveEffect("The player has been added.");
        cout << *cmd;

        // Validate command in PLAYERS ADDED state
        gameEngine->transition(GameEngine::playersAdded);
        cout << *gameEngine;
        cmd = commandProcessor->getCommand();
        commandProcessor->validate(cmd);

        while(!commandProcessor->validate(cmd) ||  cmd->getCommand() != "gamestart"){
            if(commandProcessor->validate(cmd) && cmd->getCommand() != "gamestart"){
                cmd->saveEffect("The player has been added.");
            }
            cout << *cmd;
            cmd = commandProcessor->getCommand();

        }
        cmd->saveEffect("The game has started");
        cout << *cmd;

        // Validate command in WIN state
        gameEngine->transition(GameEngine::win);
        cout << *gameEngine;
        cmd = commandProcessor->getCommand();
        commandProcessor->validate(cmd);

        while(!commandProcessor->validate(cmd)){
            commandProcessor->validate(cmd);
            cout << *cmd;
            cmd = commandProcessor->getCommand();
        }
        if(cmd->getCommand() == "quit"){
            replay = false;
            cmd->saveEffect("The game has ended.");
        }
        else{
            cmd->saveEffect("Replaying another game.");
            gameEngine->transition(GameEngine::start);

        }
        cout << *cmd;
    }

    cout << "\n\nDISPLAYING ALL COMMANDS:" << endl;
    cout << *commandProcessor;
    delete gameEngine;
    delete commandProcessor;
    gameEngine = nullptr;
    commandProcessor = nullptr;

}

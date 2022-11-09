#include "CommandProcessingDriver.h"
#include "GameEngine.h"
#include "CommandProcessing.h"
#include <iostream>
using std::cout;

void testCommandProcessor(){
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
        gameEngine->setCurrentState(GameEngine::mapLoaded);
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
        gameEngine->setCurrentState(GameEngine::mapValidated);
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
        gameEngine->setCurrentState(GameEngine::playersAdded);
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
        gameEngine->setCurrentState(GameEngine::win);
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
            gameEngine->setCurrentState(GameEngine::start);

        }
        cout << *cmd;
    }











//
//    if(commandProcessor->validate(cmd) ){
//        cmd->saveEffect("The map has been loaded.");
//        gameEngine->setCurrentState(GameEngine::mapValidated);
//        cout << *cmd;
//    }
//    else {
//        cout << *cmd;
//        while (!commandProcessor->validate(cmd)) {
//
//
//            if (commandProcessor->validate(cmd)) {
//                if (cmd->getCommand() == "validatemap") {
//                    cmd->saveEffect("The map has been validated.");
//                    gameEngine->setCurrentState(GameEngine::mapValidated);
//                    break;
//                } else {
//                    cmd->saveEffect("The map has been loaded.");
//                    cmd = commandProcessor->getCommand();
//                }
//            }
//            else{
//                cmd = commandProcessor->getCommand();
//                continue;
//            }
//            cout << *cmd;
//        }
//    }
//


//    // Validate command in MAP LOADED state
//    while(!commandProcessor->validate(cmd) || gameEngine->getCurrentState() != GameEngine::mapValidated){
//
//        cmd = commandProcessor->getCommand();
//        if(commandProcessor->validate(cmd)){
//            if(cmd->getCommand() == "validatemap"){
//                cmd->saveEffect("The map has been validated.");
//                gameEngine->setCurrentState(GameEngine::mapValidated);
//            }
//            else{
//                cmd->saveEffect("The map has been loaded.");
//            }
//        }
//        cout << *cmd;
//    }

    delete gameEngine;
    delete commandProcessor;
    gameEngine = nullptr;
    commandProcessor = nullptr;




}

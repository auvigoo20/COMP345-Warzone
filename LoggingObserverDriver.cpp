#include "LoggingObserverDriver.h"
#include "LoggingObserver.h"
#include "CommandProcessing.h"
#include "GameEngine.h"

void testLoggingObserver(){

    LogObserver* logObserver = new LogObserver();

    // TESTING COMMAND AND COMMAND PROCESSOR
    GameEngine* gameEngine = new GameEngine();
    CommandProcessor* commandProcessor = new CommandProcessor(gameEngine);
    commandProcessor->attach(logObserver);

    for(int i = 0 ; i < 3; i++){
        Command* cmd = commandProcessor->getCommand();
        cmd->attach(logObserver);
        cmd->saveEffect("Command effect test");
    }
    delete gameEngine;
    delete commandProcessor;
    gameEngine = nullptr;
    commandProcessor = nullptr;



}

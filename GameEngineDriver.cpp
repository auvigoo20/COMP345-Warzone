#include "GameEngineDriver.h"
#include "GameEngine.h"
#include "CommandProcessing.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

int testGameStates(){


    cout << "****************************************" << endl;
    cout << "*          Testing Game Engine         *" << endl;
    cout << "****************************************" << endl;

    GameEngine ge;
    ge.startupPhase();

//    bool done = false;
//    GameEngine testGameEngine {GameEngine::start};
//    Command* latestCommand;
//    CommandProcessor* commandProcessor;
//
//    cout << testGameEngine << endl;
//
//    while(!done) {
//        bool invalidCommand = true;
//
//        latestCommand->getCommand();
//
//        testGameEngine.setLatestCommand(latestCommand);
//
//        for (int i=0; i < testGameEngine.getCurrentState()->getTransitions().size(); i++) {
//            if (testGameEngine.getCurrentState()->getTransitions().at(i)->getName() == testGameEngine.getLatestCommand()->getCommand()) {
//                if (testGameEngine.getCurrentState()->getTransitions().at(i)->getTo() == nullptr) {
//                    invalidCommand = false;
//                    done = true;
//                    break;
//                }
//                testGameEngine.setCurrentState(testGameEngine.getCurrentState()->getTransitions().at(i)->getTo());
//                cout << testGameEngine << endl;
//                invalidCommand = false;
//                break;
//            }
//        }
//
//        if (invalidCommand) {
//            cout << "Invalid command." << endl;
//        }
//
//        cout << endl;
//    }
//
//    cout << "Game ended." << endl;

    return 0;
}
#include "GameEngineDriver.h"
#include "GameEngine.h"

#include <iostream>
using std::cin;
using std::cout;
#include <string>
using std::string;

int testGameStates(){

    GameEngine testGameEngine = GameEngine(GameEngine::start);
    cout << "\nCurrent State: " << *testGameEngine.getCurrentState()->getName() << "\n";

    while(true){
        bool invalidCommand = true;

        cout << "Enter a command:";
        cin >> *testGameEngine.latestCommand;

        // TEMPORARY TO BREAK LOOP
        if ("end" == *testGameEngine.latestCommand) {
            break;
        }

        for (int i=0; i < testGameEngine.getCurrentState()->getTransitions()->size(); i++) {
            if (*testGameEngine.getCurrentState()->getTransitions()->at(i)->getName() == *testGameEngine.latestCommand) {
                testGameEngine.setCurrentState(testGameEngine.getCurrentState()->getTransitions()->at(i)->getTo());
                cout << "Current State: " << *testGameEngine.getCurrentState()->getName() << "\n";
                invalidCommand = false;
                break;
            }
        }

        if (invalidCommand) {
            cout << "Invalid command.\n";
        }
    }


    return 0;
}
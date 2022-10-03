#include "GameEngineDriver.h"
#include "GameEngine.h"

#include <iostream>
using std::cin;
using std::cout;
#include <string>
using std::string;

int testGameStates(){

    bool done = false;
    GameEngine testGameEngine = GameEngine(GameEngine::start);
    cout << "\nCurrent State: " << *testGameEngine.getCurrentState()->getName() << "\n";

    while(!done) {
        bool invalidCommand = true;

        cout << "Enter a command:";
        cin >> *testGameEngine.latestCommand;

        for (int i=0; i < testGameEngine.getCurrentState()->getTransitions()->size(); i++) {
            if (*testGameEngine.getCurrentState()->getTransitions()->at(i)->getName() == *testGameEngine.latestCommand) {
                if (testGameEngine.getCurrentState()->getTransitions()->at(i)->getTo() == nullptr) {
                    invalidCommand = false;
                    done = true;
                    break;
                }
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

    cout << "Game ended.\n";

    return 0;
}
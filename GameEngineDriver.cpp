#include "GameEngineDriver.h"
#include "GameEngine.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

int testGameStates(){

    bool done = false;
    GameEngine testGameEngine {GameEngine::start};

    cout << testGameEngine << endl;

    while(!done) {
        bool invalidCommand = true;

        cout << "Enter a command:";
        cin >> testGameEngine.latestCommand;

        for (int i=0; i < testGameEngine.getCurrentState()->getTransitions().size(); i++) {
            if (testGameEngine.getCurrentState()->getTransitions().at(i)->getName() == testGameEngine.latestCommand) {
                if (testGameEngine.getCurrentState()->getTransitions().at(i)->getTo() == nullptr) {
                    invalidCommand = false;
                    done = true;
                    break;
                }
                testGameEngine.setCurrentState(testGameEngine.getCurrentState()->getTransitions().at(i)->getTo());
                cout << testGameEngine << endl;
                invalidCommand = false;
                break;
            }
        }

        if (invalidCommand) {
            cout << "Invalid command." << endl;
        }
    }

    cout << "Game ended." << endl;

    return 0;
}
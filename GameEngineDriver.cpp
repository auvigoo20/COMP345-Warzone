#include "GameEngineDriver.h"
#include "GameEngine.h"

#include <iostream>
using std::cin;
using std::cout;
#include <string>
using std::string;

int testGameStates(){

    GameEngine testGameEngine = GameEngine();

    cin >> *testGameEngine.latestCommand;
    cout << *testGameEngine.latestCommand;

    return 0;
}
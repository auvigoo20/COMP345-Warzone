#include "MapDriver.h"
#include "GameEngineDriver.h"
#include "PlayerDriver.h"
#include "OrdersDriver.h"
#include "CardsDriver.h"
#include "CommandProcessingDriver.h"
#include <string>

int main(int argc, char** argv){
    if(argc == 1){
//    testLoadMaps();
//    testPlayer();
//    testOrdersLists();
//    testCards();
//    testGameStates();
        testCommandProcessor();
    }
    else{
        if(string(argv[1]) == "-console"){
            testCommandProcessorConsole();
        }
        else if(string(argv[1]) == "-file"){
            testCommandProcessorFile(string(argv[2]));
        }
    }

    return 0;
}

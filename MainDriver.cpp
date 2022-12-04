#include "MapDriver.h"
#include "GameEngineDriver.h"
#include "PlayerDriver.h"
#include "OrdersDriver.h"
#include "CardsDriver.h"
#include "CommandProcessingDriver.h"
#include "LoggingObserverDriver.h"
#include "PlayerStrategiesDriver.h"
#include "TournamentDriver.h"
#include <string>

int main(int argc, char** argv){
    if(argc == 1){
//        testCommandProcessor();
//        testStartupPhase();
//        testOrderExecution();
//        testMainGameLoop();
//        testLoggingObserver();
            testPlayerStrategies();
//        testTournament();
    }
    else{
        if(string(argv[1]) == "-console"){
            testTournament();
        }
        else if(string(argv[1]) == "-file"){
            testTournamentFile(string(argv[2]));
        }
    }

    return 0;
}
